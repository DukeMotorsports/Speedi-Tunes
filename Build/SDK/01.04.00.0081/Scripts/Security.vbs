'
' Generate Functions
'

'
' Note: This was a work in progress. Security is currently under discussion
' and so all of this may change.
'
Sub GenBegin()

	ProjectHeader = Tag("ProjectHeader")
	SecurityIncludeFile = Tag("SecurityIncludeFile")

	OutC "#include """ & ProjectHeader & """"
	OutC "#include <ecu/sections.h>"
	OutC ""
End Sub

Sub GenUsers()
	OutC "/*"
	OutC " * Users"
	OutC " */"
	OutC ""
	Dim Users
	i = 1
	Set Users = Tags("Users")
	For Each User in Users
		OutC User
		Next
	OutC ""
	For Each User in Users
		OutC "const struct sec_user u" & i & " = { &u" & i & "_username_hash };"
		i = i + 1
		Next
End Sub

Sub GenGroups()
	OutC "/*"
	OutC " * Groups"
	OutC " */"
	OutC ""
	Dim Groups
	Set Groups = Tags("Groups")
	For Each Group in Groups
		OutC Group
		Next
End Sub

Sub GenEnd()
	Source = C
	Valid = True
End Sub
'
'		Dim PeriodicNames
'		Dim PeriodicName
'
'		' Initcalls
'		OutC "__initcall(DoOnInit);"
'		OutC ""
'
'		' Startup code for threads
'		Set	PeriodicNames = Tags("PeriodicNames")
'
'		OutC "void InitPeriodicThreads()"
'		OutC "{"
'		IncIndent
'			OutC "/* Setup Periodic Threads */"
'			For Each PeriodicName in PeriodicNames
'				OutC "ecu_thread_create(" & PeriodicName & ", 0, 0);"
'			Next
'		DecIndent
'		OutC "}"
'		OutC ""
'		Set PeriodicNames = Nothing
'
'		' Main loop
'		OutC "int main()"
'		OutC "{"
'		IncIndent
'
'			OutC "DoOnPowerOn();"
'			OutC "DoOnStartUp();"
'			OutC ""
'			OutC "InitPeriodicThreads();"
'			OutC ""
'
'			OutC "while (1)"
'			OutC "{"
'			IncIndent
'				OutC "ecu_thread_yield();"
'				OutC ""
'				OutC "if (s_restart)"
'				OutC "{"
'				IncIndent
'					OutC "DoOnRestart();"
'					OutC "s_restart = false;"
'				DecIndent
'				OutC "}"
'			DecIndent
'			OutC "}"
'			OutC ""
'			OutC "DoOnShutDown();"
'			OutC ""
'			OutC "return 0;"
'		DecIndent
'		OutC "}"
'	End Sub
