'
' Table code generation
'

'
' Public Function
' Generate declarations for Table data
'
Sub TableDeclareData()
	DataType = Tag("DataType")
	CfgSymbol = Tag("CfgSymbol")
	StateSymbol = Tag("StateSymbol")
	SectionIndex = CInt(Tag("SectionIndex"))
	BodySection = Tag("BodySection")
	BodySymbol = Tag("BodySymbol")
	NumInterpolate = CInt(Tag("NumInterpolate"))
	XAxisSize = CLng(Tag("XAxisSize"))
	XAxisMin = CLng(Tag("XAxisMin"))
	XAxisExtrapolate = Tag("XAxisExtrapolate")
	XAxisMandatory = Tag("XAxisMandatory")
	YAxisSize = CLng(Tag("YAxisSize"))
	YAxisMin = CLng(Tag("YAxisMin"))
	YAxisExtrapolate = Tag("YAxisExtrapolate")
	YAxisMandatory = Tag("YAxisMandatory")
	ZAxisSize = CLng(Tag("ZAxisSize"))
	ZAxisMin = CLng(Tag("ZAxisMin"))
	ZAxisExtrapolate = Tag("ZAxisExtrapolate")
	ZAxisMandatory = Tag("ZAxisMandatory")

	' X Axis Data
	XAxisSymbol = Tag("XAxisSymbol")

	If NumInterpolate >= 1 Then
		Call TableDeclareAxis(DataType, "XAxis", XAxisSymbol, SectionIndex, XAxisSize)
		XAxisFlag = AxisGetFlag(XAxisMandatory, XAxisExtrapolate)
	End If

	' Y Axis Data
	If NumInterpolate >= 2 Then
		YAxisSymbol = Tag("YAxisSymbol")

		Call TableDeclareAxis(DataType, "YAxis", YAxisSymbol, SectionIndex, YAxisSize)
		YAxisFlag = AxisGetFlag(YAxisMandatory, YAxisExtrapolate)
	End If

	' Z Axis Data
	If NumInterpolate = 3 Then
		ZAxisSymbol = Tag("ZAxisSymbol")

		Call TableDeclareAxis(DataType, "ZAxis", ZAxisSymbol, SectionIndex, ZAxisSize)
		ZAxisFlag = AxisGetFlag(ZAxisMandatory, ZAxisExtrapolate)
	End If

	' Body Data
	C = C & Indent & DataType & " " & TableGetSection(SectionIndex, BodySection) & " " & BodySymbol
	C = C & "[" & ZAxisSize & "][" & YAxisSize & "][" & XAxisSize & "];" & vbLf

	' Config structs
	C = C & "static " & "interp_" & NumInterpolate & "a_" & DataType & "_cfg" & " " & CfgSymbol & " = " & "INIT_INTERP_" & NumInterpolate & "A_" & UCase(DataType) & "_CFG"
	Select Case NumInterpolate
	Case 0
		OutC "(" _
			& BodySymbol _
			& ", " & XAxisSize _
			& ", " & YAxisSize _
			& ", " & ZAxisSize _
			& ", " & XAxisMin _
			& ", " & YAxisMin _
			& ", " & ZAxisMin _
			& ");"
	Case 1
		OutC "(" _
			& XAxisSymbol _
			& ", " & BodySymbol _
			& ", " & XAxisSize _
			& ", " & YAxisSize _
			& ", " & ZAxisSize _
			& ", " & YAxisMin _
			& ", " & ZAxisMin _
			& ", " & XAxisFlag _
			& ");"
	Case 2
		OutC "(" _
			& XAxisSymbol _
			& ", " & YAxisSymbol _
			& ", " & BodySymbol _
			& ", " & XAxisSize _
			& ", " & YAxisSize _
			& ", " & ZAxisSize _
			& ", " & ZAxisMin _
			& ", " & XAxisFlag _
			& ", " & YAxisFlag _
			& ");"
	Case 3
		OutC "(" _
			& XAxisSymbol _
			& ", " & YAxisSymbol _
			& ", " & ZAxisSymbol _
			& ", " & BodySymbol _
			& ", " & XAxisSize _
			& ", " & YAxisSize _
			& ", " & ZAxisSize _
			& ", " & XAxisFlag _
			& ", " & YAxisFlag _
			& ", " & ZAxisFlag _
			& ");"

	End Select

	' State
	OutC "static " & "interp_" & NumInterpolate & "a_" & DataType & "_state" & " " & StateSymbol & ";"

	Source = C
	Valid = True
End Sub

'
' Helper
' Generate code to declare (and optionally initialise) table axis data.
'
Function TableDeclareAxis(ByRef DataType, ByRef Axis, ByRef Symbol, ByVal SectionIndex, ByVal MaxSites)

	Symbol = Tag(Axis & "Symbol")
	Section = "cal"

	OutC DataType & " " & TableGetSection(SectionIndex, Section) & " " & Symbol & "[" & MaxSites & "];"
End Function

'
' Helper
' Get the correct section name for table body/axis data
'
Private Function TableGetSection(ByVal SectionIndex, ByVal Section)
	'default to calibrated table data
	If Section = "" Then
		Section = "cal"
	End If
	TableGetSection = "__ecu_" & Section & "(" & SectionIndex & ")"
End Function

Private Function AxisGetFlag(Byval Mandatory, ByVal Extrapolate)
	If Mandatory = "1" Or Extrapolate <> "" Then
		AxisGetFlag = "("
		If Mandatory = "1" Then
			AxisGetFlag = AxisGetFlag & "AXIS_F32_FLAG_MANDATORY"

			If Extrapolate <> "" Then
				AxisGetFlag = AxisGetFlag & "|"
			End If
		End If

		If Extrapolate = "Below" Then
			AxisGetFlag = AxisGetFlag & "AXIS_F32_FLAG_EXTRAPOLATE_MIN"
		ElseIf Extrapolate = "Above" Then
			AxisGetFlag = AxisGetFlag & "AXIS_F32_FLAG_EXTRAPOLATE_MAX"
		ElseIf Extrapolate = "Both" Then
			AxisGetFlag = AxisGetFlag & "AXIS_F32_FLAG_EXTRAPOLATE_BOTH"
		End if

		AxisGetFlag = AxisGetFlag & ")"
	Else
		AxisGetFlag = "0"
	End If

End Function

'
' Public Function
' Generate code for the 'Init' function for a Table
'
Sub TableInit()
	DataType = Tag("DataType")
	FuncName = Tag("FuncName")
	CfgSymbol = Tag("CfgSymbol")
	StateSymbol = Tag("StateSymbol")
	XAxisSymbol = Tag("XAxisSymbol")
	YAxisSymbol = Tag("YAxisSymbol")
	ZAxisSymbol = Tag("ZAxisSymbol")
	NumInterpolate = CInt(Tag("NumInterpolate"))

	OutC "void " & FuncName & "()"
	OutC "{"
	IncIndent

		OutC "interp_" & NumInterpolate & "a_" & DataType & "_init(&" & StateSymbol & ", &" & CfgSymbol _
			& ", " & XAxisSymbol _
			& ", " & YAxisSymbol _
			& ", " & ZAxisSymbol _
			& ");"

	DecIndent
	OutC "}"
	Source = C
	Valid = True
End Sub

'
' Public Function
' Generate code for the 'Lookup' function for a Table
'
Sub TableLookup()
	DataType = Tag("DataType")
	FuncName = Tag("FuncName")
	LValueSymbol = Tag("LValueSymbol")
	CfgSymbol = Tag("CfgSymbol")
	StateSymbol = Tag("StateSymbol")
	XAxisSymbol = Tag("XAxisSymbol")
	YAxisSymbol = Tag("YAxisSymbol")
	ZAxisSymbol = Tag("ZAxisSymbol")
	NumInterpolate = CInt(Tag("NumInterpolate"))


	OutC "void " & FuncName & "()"
	OutC "{"
	IncIndent

	OutC LValueSymbol & " = " & "interp_" & NumInterpolate & "a_" & DataType & "(&" & StateSymbol & ", &" & CfgSymbol _
		& ", " & XAxisSymbol _
		& ", " & YAxisSymbol _
		& ", " & ZAxisSymbol _
		& ");"
	DecIndent
	OutC "}"
	Source = C
	Valid = True
End Sub
