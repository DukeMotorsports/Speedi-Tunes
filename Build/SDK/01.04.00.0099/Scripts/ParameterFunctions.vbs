'
' Parameter code generation
'

'
' Public Function
' Generate declarations for Parameter data
'
Sub ParameterDeclareData()
	Symbol = Tag("Symbol")
	DataType = Tag("DataType")
	SectionIndex = CInt(Tag("SectionIndex"))

	Section = "_ecu_cal"

	OutC "_" & Section & "(" & SectionIndex & ") " & DataType & " " & Symbol & ";"
	OutH "__extern" & Section & " " & DataType & " " & Symbol & ";"

	Source = C
	Header = H
	Valid = True
End Sub
