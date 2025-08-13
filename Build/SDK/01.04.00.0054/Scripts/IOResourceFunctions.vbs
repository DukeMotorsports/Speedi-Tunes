'
' Code generation functions for IO Resources
'

'
' Public Function
' Generate code for the 'Init', 'Shutdown', 'Sync' functions for an Output
'
Sub IOResFuncGeneric()
	EventFuncName = Tag("EventFuncName")

	OutC "void " & EventFuncName & "()"
	OutC "{"
		IncIndent

		' First insert all calls to IO Resource (kernel) functions
		Dim CallID
		Dim	CallIDs
		Set CallIDs = Tags("CallIDs")

		For Each CallID in CallIDs
			CallType = Tag(CallID & ".CallType")

			If CallType = "Kernel" Then
				InsertKernelFuncCall(CallID)
			ElseIf CallType = "User" Then
				InsertUserFuncCall(CallID)
			End If
		Next

		DecIndent
	OutC "}"

	Set CallIDs = Nothing

	Source = C
	Valid = True

End Sub


Private Function InsertKernelFuncCall(ByVal CallID)
	FuncName = Tag(CallID & ".FuncName")
	DeviceName = Tag(CallID & ".DeviceName")
	FeatureName = Tag(CallID & ".FeatureName")
	IOName = Tag(CallID & ".IOName")

	FullFuncName = DeviceName & "_" & FuncName
	IOResEnum = FeatureName & "_" & IOName

	' Indent
	C = C & Indent

	' Return value
	ReturnValue = Tag(CallID & ".ReturnValue")

	If Not ReturnValue = "" Then
		C = C & ReturnValue & " = "
	End If

	' Function Name
	C = C & FullFuncName & "("

	' Arg 0 is always the enum
	C = C & IOResEnum & "/*[feature]_[id]*/"

	' optional extra args
	Dim ArgName
	Dim ArgNames
	Set ArgNames = Tags(CallID & ".ArgNames")

	For Each ArgName in ArgNames

		' Separate from previous arg
		C = C & ", "

		' The value for each arg can consist of multiple values (IE for masked params)
		' Assume they need to be or'd "|" together
		Dim ArgVal
		Dim ArgValues
		Set ArgValues = Tags(CallID & ".ArgValues." & ArgName)

		i = 0

		For Each ArgVal in ArgValues

			If i > 0 Then
				C = C & "|"
			End If

			C = C & ArgVal

			i = i + 1
		Next

		Set ArgValues = Nothing

		' Comment the arg name
		C = C & " /*[" & ArgName & "]*/"
	Next

	' close the function call
	C = C & ");" & vbLf

	Set ArgNames = Nothing
End Function


Private Function InsertUserFuncCall(ByVal CallID)
	OutC CallID & "();"
End Function
