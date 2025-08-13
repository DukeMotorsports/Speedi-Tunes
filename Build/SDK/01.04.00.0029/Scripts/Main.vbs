'
' Generate Functions
'

'
' Public Function
' Generate motec.h
'
Sub GenProjectHdr()

	HeaderGuard = Tag("HeaderGuard")
	HardwareHeader = Tag("HardwareHeader")

	OutC "#if !defined(" & HeaderGuard & ")"
	OutC "#define " & HeaderGuard
	OutC ""
	OutC "#include """ & HardwareHeader & """"
	OutC ""

	' core system system headers
	OutC "#include <ecu/thread.h>"

	' Library file includes
	Dim LibIncludeFiles
	Set LibIncludeFiles = Tags("LibIncludeFiles")

	For Each IncludeFile in LibIncludeFiles
		OutC "#include <ecu/" & IncludeFile & ">"
	Next

	Set LibIncludeFiles = Nothing

	' The funcs in these headers are not available as library funcs
	' So for now we need to include them explicitly here
	OutC "#include <ecu/table.h>"
	OutC "#include <ecu/timer.h>"

	OutC ""

	' built-in declaration
	BuiltInDecl	= Tag("BuiltInDecl")
	OutC BuiltInDecl

	' Enums for user-supplied data types
	Dim DataTypeNames
	Set DataTypeNames = Tags("DataTypeNames")

	For Each DataTypeName in DataTypeNames
		OutC "typedef enum {"

		Dim SymbolNames
		Set SymbolNames = Tags(DataTypeName & ".SymbolNames")

		For Each SymbolName in SymbolNames
			SymValue = Tag(SymbolName & ".Value")
			OutC vbTab & SymbolName & " = " & SymValue & ","
		Next

		Set SymbolNames = Nothing

		OutC "} " & DataTypeName & ";"
		OutC ""
	Next

	Set DataTypeNames = Nothing

	OutC "#endif /* " & HeaderGuard & " */"

	Source = C
	Valid = True
End Sub


Sub GenBegin()

	ProjectHeader = Tag("ProjectHeader")

	OutC "#include """ & ProjectHeader & """"

	Dim IncludeFiles
	Set IncludeFiles = Tags("IncludeFiles")

	For Each IncludeFile in IncludeFiles
		OutC "#include """ & IncludeFile & """"
	Next

	Set IncludeFiles = Nothing

	OutC ""

	Valid = True
End Sub

Sub GenInfo()

	OutC "/* information that the firmware may be asked for by the PC */"
	OutC "#if 0"
	OutC "static firmware_info __info s_fw_info ="
	OutC "{"
	IncIndent
		OutC Tag("VersionMajor") 	& ","
		OutC Tag("VersionMinor") 	& ","
		OutC Tag("BuildNumber")
	DecIndent
	OutC "};"
	OutC "#endif"
	OutC ""

	Valid = True
End Sub

Sub GenBody()

	' initcalls, exitcalls etc.
	GenXXCalls()
	OutC ""

	' Startup code for threads
	GenPeriodicCalls()
	OutC ""

	' Main loop
	OutC "/* Main */"
	OutC "void __attribute__((externally_visible)) fw_main(void)"
	OutC "{"
	IncIndent

		OutC "InitPeriodicThreads();"
		OutC ""
		OutC "ecu_run();"
		OutC ""
		OutC "StopPeriodicThreads();"
		OutC "JoinPeriodicThreads();"
	DecIndent
	OutC "}"

	Valid = True
End Sub

Private Function GenXXCalls()

	Dim		FuncName
	Dim		XXCalls
	Set		XXCalls = Tags("XXCalls")

	OutC "/* Initcalls / Exitcalls */"
	For Each FuncName In XXCalls
		CallType = Tag("XXCalls." & FuncName & ".CallType")

		OutC "__" & CallType & "(" & FuncName & ");"
	Next

	Set XXCalls = Nothing
End Function

Private Function GenPeriodicCalls()
	Dim PeriodicNames
	Dim PeriodicName

	' Startup code for threads
	Set	PeriodicNames = Tags("Periodic")

	OutC "/* Periodic Threads */"
	For Each PeriodicName in PeriodicNames
		OutC "static ecu_thread_t __" & PeriodicName & ";"
	Next
	OutC ""
	OutC "/* Setup Periodic Threads */"
	OutC "void InitPeriodicThreads(void)"
	OutC "{"
	IncIndent
		For Each PeriodicName in PeriodicNames
			OutC "__" & PeriodicName & " = ecu_thread_create("
			IncIndent
			if (Mid(PeriodicName,1,11) = "Events__On_") then
			    OutC PeriodicName & ", """ & Mid(PeriodicName,12) _
				    & """, " & Tag("PeriodicPriority." & PeriodicName)
			else
			    OutC PeriodicName & ", """ & PeriodicName _
				    & """, " & Tag("PeriodicPriority." & PeriodicName)
			End if
			DecIndent
			OutC ");"
		Next
	DecIndent
	OutC "}"
	OutC ""
	OutC "/* Cancel Periodic Threads */"
	OutC "void StopPeriodicThreads(void)"
	OutC "{"
	IncIndent
		For Each PeriodicName in PeriodicNames
			OutC "ecu_thread_cancel(__" & PeriodicName & ");"
		Next
	DecIndent
	OutC "}"
	OutC ""
	OutC "/* Join Periodic Threads */"
	OutC "void JoinPeriodicThreads(void)"
	OutC "{"
	IncIndent
		For Each PeriodicName in PeriodicNames
			OutC "ecu_thread_join(__" & PeriodicName & ");"
		Next
	DecIndent
	OutC "}"

	Set PeriodicNames = Nothing
End Function

Sub GenEnd()
	Source = C
	Valid = True
End Sub
