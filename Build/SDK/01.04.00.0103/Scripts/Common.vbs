
'
' Globals used by code helper funcs
'
Dim C
Dim H
Dim Indent


'
' Code output helper functions
'
Sub IncIndent
	Indent = Indent & vbTab
End Sub

Sub DecIndent
	If Len(Indent) <= 1 Then
		Indent = vbNullString
	Else
		Indent = Left(Indent, Len(Indent) - 1)
	End If
End Sub

Sub OutC(line)
	C = C & Indent & line & vbLf
End Sub

Sub OutH(line)
	H = H & line & vbLf
End Sub
