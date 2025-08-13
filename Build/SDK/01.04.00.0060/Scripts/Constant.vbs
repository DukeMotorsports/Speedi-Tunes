'
' Constant code generation
'

'
' Public Function
' Generate a declaration for a Constant that is not an enum
'
Sub ConstantDeclareData()
	DataType = Tag("DataType")
	Symbol = Tag("Symbol")
	ConstValue = Tag("ConstValue")

	OutH "#define " & Symbol & vbTab & vbTab & "((" & DataType & ") " & ConstValue & ")"

	Header = H
	Valid = True
End Sub

'
' Public Function
' Generate a declaration for a Constant that is an enum
'
Sub ConstantDeclareEnum()
	Symbol = Tag("Symbol")
	ConstValue = Tag("ConstValue")

	OutH "#define " & Symbol & vbTab & vbTab & ConstValue

	Header = H
	Valid = True
End Sub
