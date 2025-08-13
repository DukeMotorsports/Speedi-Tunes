'
' Group code generation
'

'
' Public Function
' Generate code for the begining of a group .h file
'
Sub GroupBeginHeader()
	HeaderGuard = Tag("HeaderGuard")

	OutC "#if !defined(" & HeaderGuard & ")"
	OutC "#define " & HeaderGuard

	Source = C
	Valid = True
End Sub

'
' Public Function
' Generate code for the end of a group .h file
'
Sub GroupEndHeader()
	HeaderGuard = Tag("HeaderGuard")

	OutC ""
	OutC "#endif /* " & HeaderGuard & " */"

	Source = C
	Valid = True
End Sub


'
' Public Function
' Generate code for the beginning of a group .c file
'
Sub GroupBeginSource()
	Dim IncludeFiles

	ProjectHeader = Tag("ProjectHeader")
	Set IncludeFiles = Tags("IncludeFiles")

	OutC "#include """ & ProjectHeader & """"

	For Each IncludeFile in IncludeFiles
		OutC "#include """ & IncludeFile & """"
	Next

	Set IncludeFiles = Nothing

	Source = C
	Valid = True
End Sub
