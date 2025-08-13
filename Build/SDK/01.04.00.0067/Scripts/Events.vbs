'
' Code generation functions for IO Resources
'

'
' Public Function
' Generate code for an event body
'
Sub KernelPeriodicEventBody()
	FuncName = Tag("FuncName")
	Interval = Tag("Interval")
	EventTrigger = Tag("Trigger")

	Dim FuncCall
	Dim FuncCalls

	Set FuncCalls = Tags("FuncCalls")

	If NOT IsNull(Interval) AND Interval <> "" then
		EventTrigger = "TRIGGER_" & Interval
	End If

	OutH "void " & FuncName & "(void);"

	OutC "void " & FuncName & "(void)"
	OutC "{"
		IncIndent

		OutC "do {"

		IncIndent

			OutC "ecu_thread_testcancel();"
			OutC ""

			For Each FuncCall In FuncCalls
				OutC FuncCall & "();"
			Next

		DecIndent

		OutC "} while (trigger_wait(" & EventTrigger & ") > 0);"

		DecIndent
	OutC "}"

	Set FuncCalls = Nothing

	Source = C
	Valid = True

End Sub


'
' Public Function
' Generate code for an event body
'
Sub CommonRunOnceEventBody()
	FuncName = Tag("FuncName")

	Dim FuncCall
	Dim FuncCalls

	Set FuncCalls = Tags("FuncCalls")

	OutH "void " & FuncName & "(void);"

	OutC "void " & FuncName & "(void)"
	OutC "{"
		IncIndent

		For Each FuncCall In FuncCalls
			OutC FuncCall & "();"
		Next

		DecIndent
	OutC "}"

	Set FuncCalls = Nothing

	Source = C
	Valid = True

End Sub


'
' Public Function
' Generate code for dual rate event mode switch
'
Sub DualRateEventModeSwitch()
	FuncName = Tag("FuncName")
	EventTrigger = Tag("Trigger")
	Interval = Tag("Interval")

	OutH "void " & FuncName & "(void);"

	OutC "void " & FuncName & "(void)"
	OutC "{"
		IncIndent
		OutC EventTrigger & " = TRIGGER_" & Interval & ";"
		DecIndent
	OutC "}"

	Set FuncCalls = Nothing

	Source = C
	Valid = True

End Sub

' Public Function
' Generate a declaration for a Dual Rate Event's trigger
'
Sub DualRateEventTriggerDeclareData()
	Trigger         = Tag("Trigger")
	DefaultInterval = Tag("DefaultInterval")

	OutC "static u32 " & Trigger & " = TRIGGER_" & DefaultInterval & ";"

	Source = C
	Valid = True
End Sub
