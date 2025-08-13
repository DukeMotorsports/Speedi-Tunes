'
' Code generation functions for IO Resource Names
'

'
' Public Function
' Generate declarations for IO Resource Name constant Data
'
Sub IOResNameConstantDeclareData()
	Symbol = Tag("Symbol")
    DataType = "CIOResourceIdent"

	OutC "const " & DataType & " "  & Symbol & " = {"
		IncIndent

		' First insert all calls to IO Resource (kernel) functions
		Dim FieldName
		Dim	FieldNames
        Dim FieldValues
		Set FieldNames = Tags("FieldNames")
        Set FieldValues = Tags("FieldValues")

        i = 0
		For Each FieldName in FieldNames
            Outc "." & FieldName & " = " & FieldValues(i) & ","
            i = i + 1
		Next

		DecIndent
	OutC "};"

    OutH "extern const " & DataType & " " & Symbol  & ";"

    Set FieldNames = Nothing
	Set FieldValues = Nothing

	Source = C
    Header = H
	Valid = True

End Sub

'
' Public Function
' Generate declarations for IO Resource Name Parameter data
'
Sub IOResNameParameterDeclareData()
	Symbol = Tag("Symbol")
	SectionIndex = CInt(Tag("SectionIndex"))
    DataType = "CIOResourceIdent"

	Section = "_ecu_cal"

	OutC "_" & Section & "(" & SectionIndex & ") " & DataType & " " & Symbol & ";"
	OutH "__extern" & Section & " " & DataType & " " & Symbol & ";"

	Source = C
	Header = H
	Valid = True
End Sub
