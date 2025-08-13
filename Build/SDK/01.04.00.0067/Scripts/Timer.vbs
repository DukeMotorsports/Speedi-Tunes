'
' Timer code generation
'

'
' Public Function
' Generate declarations for Timer data
'
Sub TimerDeclareData()
	DataType = Tag("DataType")
	StateSymbol = Tag("StateSymbol")

	OutC "static " & "timer_" & DataType & "_state " & StateSymbol & ";"

	Source = C
	Valid = True
End Sub

'
' Public Function
' Generate the 'Set' function call
'
Sub TimerSet()
	FuncName = Tag("FuncName")
	StateSymbol = Tag("StateSymbol")
	FuncParamSignature = Tag("FuncParamSignature")
	DataType = Tag("DataType")

	ParamTimeoutName = "Timeout"

	OutC "void " & FuncName & "(" & FuncParamSignature & ")"
	OutC "{"
	IncIndent

		OutC "timer_set_" & DataType & "(&" & StateSymbol & ", " & ParamTimeoutName & ");"

	DecIndent
	OutC "}"

	Source = C
	Valid = True
End Sub


'
' Public Function
' Generate the 'Remaining' function call
'
Sub TimerRemaining()
	FuncName = Tag("FuncName")
	StateSymbol = Tag("StateSymbol")
	FuncParamSignature = Tag("FuncParamSignature")
	FuncReturnType = Tag("FuncReturnType")
	DataType = Tag("DataType")

	OutC FuncReturnType & " " & FuncName & "(" & FuncParamSignature & ")"
	OutC "{"
	IncIndent

		OutC "return timer_remaining_" & DataType & "(&" & StateSymbol & ");"

	DecIndent
	OutC "}"

	Source = C
	Valid = True
End Sub
