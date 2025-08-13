'
' Compile/link functions
'

'
' Public Function
' Generate compiler command-line
'
Sub GenCompileCommand()
	SDKPath = Tag("SDKPath")
	GCCPath = Tag("GCCPath") & "\5.1.0"
	GCCLibPath = GCCPath & "\lib"
	Target = Tag("Target")
	SourceFiles = Tag("SourceFiles")

	OutputFile = Target & "_dbg.elf"
	Command = """" & GCCPath & "\bin\powerpc-eabispe-gcc.exe"""
	Args = 	" -mspe=no -mabi=no-spe -msdata=none" _
			& " -g" _
			& " -nostdinc" _
			& " -Werror -Wstrict-prototypes -fshort-double" _
			& " -std=gnu99 -fomit-frame-pointer" _
			& " -Wsign-compare -Werror-implicit-function-declaration" _
			& " -Wall -Wframe-larger-than=2048" _
			& " -fomit-frame-pointer -fno-stack-protector" _
			& " -Os" _
			& " -D_ECU_SOURCE" _
			& " -I """ & SDKPath & "\include""" _
			& " -fwhole-program -static -n -z max-page-size=4096" _
			& " -o """ & OutputFile & """" _
			& " -nostdlib -L""" & SDKPath & "\mk"" -Tecu.ld" _
			& " """ & GCCLibPath & "\ecrti.o""" _
			& " """ & SDKPath & "\lib\crt0.o""" _
			& " " & SourceFiles _
			& " """ & SDKPath & "\lib\libecu.a""" _
			& " """ & SDKPath & "\lib\libc.a""" _
			& " """ & GCCLibPath & "\libgcc.a""" _
			& " """ & GCCLibPath & "\ecrtn.o"""

	Tag("Command") = Command
	Tag("Args") = Args
	Tag("OutputFile") = OutputFile
	Tag("Strip") = True

	Valid = True
End Sub


'
' Public Function
' Generate linker command-line
'
Sub GenStripCommand()
	GCCPath = Tag("GCCPath") & "\5.1.0"
	InputFile = Tag("InputFile")
	Target = Tag("Target")

	OutputFile = Target & "_rel.elf"
	Command = """" & GCCPath & "\bin\powerpc-eabispe-strip.exe"""
	Args = 	" -o """ & OutputFile & """" _
			& " """ & InputFile & """"

	Tag("Command") = Command
	Tag("Args") = Args
	Tag("OutputFile") = OutputFile

	Valid = True
End Sub

'
' compile option to compile source
'
Function CompileArgs(SDKPath)
	CompileArgs = 	" -c -mspe=no " _
					& " -Wall" _
					& " -Os" _
					& " -D_ECU_SOURCE -D__BIG_ENDIAN_BITFIELD -D__BIG_ENDIAN" _
					& " -I """ & SDKPath & "\include"""
End Function

'
' Public Function
' Generate compile fucion command-line
'
Sub GenCompileFunctionCommand()
	SDKPath = Tag("SDKPath")
	GCCPath = Tag("GCCPath") & "\5.1.0"
	Target = Tag("Target")
	SourceFiles = Tag("SourceFiles")

	OutputFile = Target
	Command = """" & GCCPath & "\bin\powerpc-eabispe-gcc.exe"""
	Args = 	CompileArgs(SDKPath) _
			& " -o """ & OutputFile & """" _
			& " " & SourceFiles _

	Tag("Command") = Command
	Tag("CompileArgs") = Args
	Tag("OutputFile") = OutputFile
	Tag("Strip") = True

	Valid = True
End Sub

'
' Public Function
' Generate strip command for function
'
Sub GenStripFunctionCommand()
	GCCPath = Tag("GCCPath") & "\5.1.0"
	InputFile = Tag("InputFile")

	OutputFile = InputFile
	Command = """" & GCCPath & "\bin\powerpc-eabispe-strip.exe"""
	Args = 	" -g  --strip-unneeded """ & OutputFile & """"

	Tag("Command") = Command
	Tag("StripFunctionArgs") = Args
	Tag("OutputFile") = OutputFile

	Valid = True
End Sub

'
' Public Function
' specify tool set
'
Sub GetCompileToolSet()
	SDKPath = Tag("SDKPath")
	GCCPath = Tag("GCCPath") & "\5.1.0"

	Command = GCCPath & "\bin\powerpc-eabispe-gcc.exe"
	Args = CompileArgs(SDKPath)

	Tag("Command") = Command
	Tag("CompileArgs") = Args
	Tag("Archiver") = GCCPath & "\bin\powerpc-eabispe-ar.exe"
	Tag("ObjDump") = GCCPath & "\bin\powerpc-eabispe-objdump.exe"

	Valid = True
End Sub