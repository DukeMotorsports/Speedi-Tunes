'
' Channel code generation
'

'
' Public Function
' Generate declarations for Channel data
'
Sub ChannelDeclareData()
	Symbol = Tag("Symbol")
	DataType = Tag("DataType")
	Storage = Tag("Storage")
	SectionIndex = CInt(Tag("SectionIndex"))

	Section = "_ecu_data"

	If Storage = "Flash" Then
		Section = "_ecu_fdata"
	ElseIf Storage = "BatteryBacked" Then
		Section = "_ecu_bdata"
	End If

	OutC "_" & Section & "(" & SectionIndex & ") " & DataType & " " & Symbol & ";"
	OutH "__extern" & Section & " " & DataType & " " & Symbol & ";"

	Source = C
	Header = H
	Valid = True
End Sub
