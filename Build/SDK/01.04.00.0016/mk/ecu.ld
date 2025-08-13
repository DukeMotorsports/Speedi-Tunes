OUTPUT_FORMAT("elf32-powerpc", "elf32-powerpc", "elf32-powerpc")
OUTPUT_ARCH(powerpc)
ENTRY(_start)
INCLUDE config.ld
PHDRS
{
	text PT_LOAD FILEHDR PHDRS;
	data PT_LOAD;
}
SECTIONS
{
	. = USER_TEXT_VA + SIZEOF_HEADERS;
	__text = .;
	.text : {
		*(.text)
		*(.text.*)
	} : text = 0xff

	.init : ALIGN(4) {
		KEEP (*(EXCLUDE_FILE (*crtn.o) .init))
		KEEP (*(SORT(.init.*)))
		KEEP (*(.init))
	} : text = 0xff

	.fini : ALIGN(4) {
		KEEP (*(EXCLUDE_FILE (*crtn.o) .fini))
		KEEP (*(SORT(.fini.*)))
		KEEP (*(.fini))
	} : text = 0xff
	__etext = .;

	.rodata : ALIGN(4) {
		*(.rodata)
		*(.rodata.*)
	} : text

	.ctors : ALIGN(4) {
		KEEP (*(EXCLUDE_FILE (*crtn.o) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
	} : text

	.dtors : ALIGN(4) {
		KEEP (*(EXCLUDE_FILE (*crtn.o) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
	} : text

	.initcalls : ALIGN(4) {
		__INITCALL_LIST__ = .;
		KEEP (*(SORT(.initcall.*)))
		__INITCALL_END__ = .;
	} : text

	.exitcalls : ALIGN(4) {
		__EXITCALL_LIST__ = .;
		KEEP (*(SORT(.exitcall.*)))
		__EXITCALL_END__ = .;
	} : text

	.PPC.EMB.apuinfo : {
		*(.PPC.EMB.apuinfo)
	} : text

	.ecu_mem_cal : {
		*(.ecu_mem_cal)
	} : text

	.ecu_mem_data : {
		*(.ecu_mem_data)
	} : text

	.ecu_mem_bdata : {
		*(.ecu_mem_bdata)
	} : text

	.ecu_mem_fdata : {
		*(.ecu_mem_fdata)
	} : text

	. = USER_DATA_VA;
	__data = .;
	.sdata2 : ALIGN(4) { /* -msdata=eabi */
		*(.sdata2)
	} : data

	.PPC.EMB.sdata2 : ALIGN(4) { /* -msdata=eabi */
		*(.PPC.EMB.sdata2)
	} : data

	.PPC.EMB.sbss2 : ALIGN(4) { /* -msdata=eabi */
		*(.sbss2)
	} : data

	.data : ALIGN(4) {
		*(.data)
		*(.data.*)
	} : data

        /* REVISIT: got2 is only for relocatable code. This can be
         * eliminated if we supply our own __eabi() */
	.got2 : ALIGN(4) {
		*(.got2)
	} : data

	.sdata : ALIGN(4) {
		*(.sdata)
		*(.sdata.*)
	} : data

	.premalloc : ALIGN(32) {
		*(.premalloc)
	} : data

	__edata = .;

	. = ALIGN(4);
	__bss = . ;
	.sbss .  : {
		*(.sbss)
		*(.sbss.*)
	} : data

	.bss .  : {
		*(.bss)
		*(.bss.*)
		*(COMMON)
	} : data

	.ecu_shared : {
		*(.ecu_shared)
	} : data

	.ecu_data : ALIGN(4) {
		__ecu_data0 = .;
		*(.ecu_data0)
		__ecu_data1 = .;
		*(.ecu_data1)
		__ecu_data2 = .;
		*(.ecu_data2)
		__ecu_data3 = .;
		*(.ecu_data3)
		__ecu_data4 = .;
		*(.ecu_data4)
		__ecu_data5 = .;
		*(.ecu_data5)
		__ecu_data6 = .;
		*(.ecu_data6)
		__ecu_data7 = .;
		*(.ecu_data7)
		__ecu_data8 = .;
		*(.ecu_data8)
		__ecu_data9 = .;
		*(.ecu_data9)
		__ecu_data10 = .;
		*(.ecu_data10)
		__ecu_data11 = .;
		*(.ecu_data11)
		__ecu_data12 = .;
		*(.ecu_data12)
		__ecu_data13 = .;
		*(.ecu_data13)
		__ecu_data14 = .;
		*(.ecu_data14)
		__ecu_data15 = .;
		*(.ecu_data15)
		__ecu_data16 = .;
		*(.ecu_data16)
		__ecu_data17 = .;
		*(.ecu_data17)
		__ecu_data18 = .;
		*(.ecu_data18)
		__ecu_data19 = .;
		*(.ecu_data19)
		__ecu_data20 = .;
		*(.ecu_data20)
		__ecu_data21 = .;
		*(.ecu_data21)
		__ecu_data22 = .;
		*(.ecu_data22)
		__ecu_data23 = .;
		*(.ecu_data23)
		__ecu_data24 = .;
		*(.ecu_data24)
		__ecu_data25 = .;
		*(.ecu_data25)
		__ecu_data26 = .;
		*(.ecu_data26)
		__ecu_data27 = .;
		*(.ecu_data27)
		__ecu_data28 = .;
		*(.ecu_data28)
		__ecu_data29 = .;
		*(.ecu_data29)
		__ecu_data30 = .;
		*(.ecu_data30)
		__ecu_data31 = .;
		*(.ecu_data31)
		__ecu_data32 = .;
		*(.ecu_data32)
		__ecu_data33 = .;
		*(.ecu_data33)
		__ecu_data34 = .;
		*(.ecu_data34)
		__ecu_data35 = .;
		*(.ecu_data35)
		__ecu_data36 = .;
		*(.ecu_data36)
		__ecu_data37 = .;
		*(.ecu_data37)
		__ecu_data38 = .;
		*(.ecu_data38)
		__ecu_data39 = .;
		*(.ecu_data39)
		__ecu_data40 = .;
		*(.ecu_data40)
		__ecu_data41 = .;
		*(.ecu_data41)
		__ecu_data42 = .;
		*(.ecu_data42)
		__ecu_data43 = .;
		*(.ecu_data43)
		__ecu_data44 = .;
		*(.ecu_data44)
		__ecu_data45 = .;
		*(.ecu_data45)
		__ecu_data46 = .;
		*(.ecu_data46)
		__ecu_data47 = .;
		*(.ecu_data47)
		__ecu_data48 = .;
		*(.ecu_data48)
		__ecu_data49 = .;
		*(.ecu_data49)
		__ecu_data50 = .;
		*(.ecu_data50)
		__ecu_data51 = .;
		*(.ecu_data51)
		__ecu_data52 = .;
		*(.ecu_data52)
		__ecu_data53 = .;
		*(.ecu_data53)
		__ecu_data54 = .;
		*(.ecu_data54)
		__ecu_data55 = .;
		*(.ecu_data55)
		__ecu_data56 = .;
		*(.ecu_data56)
		__ecu_data57 = .;
		*(.ecu_data57)
		__ecu_data58 = .;
		*(.ecu_data58)
		__ecu_data59 = .;
		*(.ecu_data59)
		__ecu_data60 = .;
		*(.ecu_data60)
		__ecu_data61 = .;
		*(.ecu_data61)
		__ecu_data62 = .;
		*(.ecu_data62)
		__ecu_data63 = .;
		*(.ecu_data63)
		__ecu_data_end = .;
	} : data

	.ecu_fdata : ALIGN(4) {
		__ecu_fdata0 = .;
		*(.ecu_fdata0)
		__ecu_fdata1 = .;
		*(.ecu_fdata1)
		__ecu_fdata2 = .;
		*(.ecu_fdata2)
		__ecu_fdata3 = .;
		*(.ecu_fdata3)
		__ecu_fdata4 = .;
		*(.ecu_fdata4)
		__ecu_fdata5 = .;
		*(.ecu_fdata5)
		__ecu_fdata6 = .;
		*(.ecu_fdata6)
		__ecu_fdata7 = .;
		*(.ecu_fdata7)
		__ecu_fdata8 = .;
		*(.ecu_fdata8)
		__ecu_fdata9 = .;
		*(.ecu_fdata9)
		__ecu_fdata10 = .;
		*(.ecu_fdata10)
		__ecu_fdata11 = .;
		*(.ecu_fdata11)
		__ecu_fdata12 = .;
		*(.ecu_fdata12)
		__ecu_fdata13 = .;
		*(.ecu_fdata13)
		__ecu_fdata14 = .;
		*(.ecu_fdata14)
		__ecu_fdata15 = .;
		*(.ecu_fdata15)
		__ecu_fdata16 = .;
		*(.ecu_fdata16)
		__ecu_fdata17 = .;
		*(.ecu_fdata17)
		__ecu_fdata18 = .;
		*(.ecu_fdata18)
		__ecu_fdata19 = .;
		*(.ecu_fdata19)
		__ecu_fdata20 = .;
		*(.ecu_fdata20)
		__ecu_fdata21 = .;
		*(.ecu_fdata21)
		__ecu_fdata22 = .;
		*(.ecu_fdata22)
		__ecu_fdata23 = .;
		*(.ecu_fdata23)
		__ecu_fdata24 = .;
		*(.ecu_fdata24)
		__ecu_fdata25 = .;
		*(.ecu_fdata25)
		__ecu_fdata26 = .;
		*(.ecu_fdata26)
		__ecu_fdata27 = .;
		*(.ecu_fdata27)
		__ecu_fdata28 = .;
		*(.ecu_fdata28)
		__ecu_fdata29 = .;
		*(.ecu_fdata29)
		__ecu_fdata30 = .;
		*(.ecu_fdata30)
		__ecu_fdata31 = .;
		*(.ecu_fdata31)
		__ecu_fdata32 = .;
		*(.ecu_fdata32)
		__ecu_fdata33 = .;
		*(.ecu_fdata33)
		__ecu_fdata34 = .;
		*(.ecu_fdata34)
		__ecu_fdata35 = .;
		*(.ecu_fdata35)
		__ecu_fdata36 = .;
		*(.ecu_fdata36)
		__ecu_fdata37 = .;
		*(.ecu_fdata37)
		__ecu_fdata38 = .;
		*(.ecu_fdata38)
		__ecu_fdata39 = .;
		*(.ecu_fdata39)
		__ecu_fdata40 = .;
		*(.ecu_fdata40)
		__ecu_fdata41 = .;
		*(.ecu_fdata41)
		__ecu_fdata42 = .;
		*(.ecu_fdata42)
		__ecu_fdata43 = .;
		*(.ecu_fdata43)
		__ecu_fdata44 = .;
		*(.ecu_fdata44)
		__ecu_fdata45 = .;
		*(.ecu_fdata45)
		__ecu_fdata46 = .;
		*(.ecu_fdata46)
		__ecu_fdata47 = .;
		*(.ecu_fdata47)
		__ecu_fdata48 = .;
		*(.ecu_fdata48)
		__ecu_fdata49 = .;
		*(.ecu_fdata49)
		__ecu_fdata50 = .;
		*(.ecu_fdata50)
		__ecu_fdata51 = .;
		*(.ecu_fdata51)
		__ecu_fdata52 = .;
		*(.ecu_fdata52)
		__ecu_fdata53 = .;
		*(.ecu_fdata53)
		__ecu_fdata54 = .;
		*(.ecu_fdata54)
		__ecu_fdata55 = .;
		*(.ecu_fdata55)
		__ecu_fdata56 = .;
		*(.ecu_fdata56)
		__ecu_fdata57 = .;
		*(.ecu_fdata57)
		__ecu_fdata58 = .;
		*(.ecu_fdata58)
		__ecu_fdata59 = .;
		*(.ecu_fdata59)
		__ecu_fdata60 = .;
		*(.ecu_fdata60)
		__ecu_fdata61 = .;
		*(.ecu_fdata61)
		__ecu_fdata62 = .;
		*(.ecu_fdata62)
		__ecu_fdata63 = .;
		*(.ecu_fdata63)
		__ecu_fdata_end = .;
	} : data

	.ecu_bdata : ALIGN(4) {
		__ecu_bdata0 = .;
		*(.ecu_bdata0)
		__ecu_bdata1 = .;
		*(.ecu_bdata1)
		__ecu_bdata2 = .;
		*(.ecu_bdata2)
		__ecu_bdata3 = .;
		*(.ecu_bdata3)
		__ecu_bdata4 = .;
		*(.ecu_bdata4)
		__ecu_bdata5 = .;
		*(.ecu_bdata5)
		__ecu_bdata6 = .;
		*(.ecu_bdata6)
		__ecu_bdata7 = .;
		*(.ecu_bdata7)
		__ecu_bdata8 = .;
		*(.ecu_bdata8)
		__ecu_bdata9 = .;
		*(.ecu_bdata9)
		__ecu_bdata10 = .;
		*(.ecu_bdata10)
		__ecu_bdata11 = .;
		*(.ecu_bdata11)
		__ecu_bdata12 = .;
		*(.ecu_bdata12)
		__ecu_bdata13 = .;
		*(.ecu_bdata13)
		__ecu_bdata14 = .;
		*(.ecu_bdata14)
		__ecu_bdata15 = .;
		*(.ecu_bdata15)
		__ecu_bdata16 = .;
		*(.ecu_bdata16)
		__ecu_bdata17 = .;
		*(.ecu_bdata17)
		__ecu_bdata18 = .;
		*(.ecu_bdata18)
		__ecu_bdata19 = .;
		*(.ecu_bdata19)
		__ecu_bdata20 = .;
		*(.ecu_bdata20)
		__ecu_bdata21 = .;
		*(.ecu_bdata21)
		__ecu_bdata22 = .;
		*(.ecu_bdata22)
		__ecu_bdata23 = .;
		*(.ecu_bdata23)
		__ecu_bdata24 = .;
		*(.ecu_bdata24)
		__ecu_bdata25 = .;
		*(.ecu_bdata25)
		__ecu_bdata26 = .;
		*(.ecu_bdata26)
		__ecu_bdata27 = .;
		*(.ecu_bdata27)
		__ecu_bdata28 = .;
		*(.ecu_bdata28)
		__ecu_bdata29 = .;
		*(.ecu_bdata29)
		__ecu_bdata30 = .;
		*(.ecu_bdata30)
		__ecu_bdata31 = .;
		*(.ecu_bdata31)
		__ecu_bdata32 = .;
		*(.ecu_bdata32)
		__ecu_bdata33 = .;
		*(.ecu_bdata33)
		__ecu_bdata34 = .;
		*(.ecu_bdata34)
		__ecu_bdata35 = .;
		*(.ecu_bdata35)
		__ecu_bdata36 = .;
		*(.ecu_bdata36)
		__ecu_bdata37 = .;
		*(.ecu_bdata37)
		__ecu_bdata38 = .;
		*(.ecu_bdata38)
		__ecu_bdata39 = .;
		*(.ecu_bdata39)
		__ecu_bdata40 = .;
		*(.ecu_bdata40)
		__ecu_bdata41 = .;
		*(.ecu_bdata41)
		__ecu_bdata42 = .;
		*(.ecu_bdata42)
		__ecu_bdata43 = .;
		*(.ecu_bdata43)
		__ecu_bdata44 = .;
		*(.ecu_bdata44)
		__ecu_bdata45 = .;
		*(.ecu_bdata45)
		__ecu_bdata46 = .;
		*(.ecu_bdata46)
		__ecu_bdata47 = .;
		*(.ecu_bdata47)
		__ecu_bdata48 = .;
		*(.ecu_bdata48)
		__ecu_bdata49 = .;
		*(.ecu_bdata49)
		__ecu_bdata50 = .;
		*(.ecu_bdata50)
		__ecu_bdata51 = .;
		*(.ecu_bdata51)
		__ecu_bdata52 = .;
		*(.ecu_bdata52)
		__ecu_bdata53 = .;
		*(.ecu_bdata53)
		__ecu_bdata54 = .;
		*(.ecu_bdata54)
		__ecu_bdata55 = .;
		*(.ecu_bdata55)
		__ecu_bdata56 = .;
		*(.ecu_bdata56)
		__ecu_bdata57 = .;
		*(.ecu_bdata57)
		__ecu_bdata58 = .;
		*(.ecu_bdata58)
		__ecu_bdata59 = .;
		*(.ecu_bdata59)
		__ecu_bdata60 = .;
		*(.ecu_bdata60)
		__ecu_bdata61 = .;
		*(.ecu_bdata61)
		__ecu_bdata62 = .;
		*(.ecu_bdata62)
		__ecu_bdata63 = .;
		*(.ecu_bdata63)
		__ecu_bdata_end = .;
	} : data

	.ecu_cal : ALIGN(4) {
		__ecu_cal0 = .;
		*(.ecu_cal0)
		__ecu_cal1 = .;
		*(.ecu_cal1)
		__ecu_cal2 = .;
		*(.ecu_cal2)
		__ecu_cal3 = .;
		*(.ecu_cal3)
		__ecu_cal4 = .;
		*(.ecu_cal4)
		__ecu_cal5 = .;
		*(.ecu_cal5)
		__ecu_cal6 = .;
		*(.ecu_cal6)
		__ecu_cal7 = .;
		*(.ecu_cal7)
		__ecu_cal8 = .;
		*(.ecu_cal8)
		__ecu_cal9 = .;
		*(.ecu_cal9)
		__ecu_cal10 = .;
		*(.ecu_cal10)
		__ecu_cal11 = .;
		*(.ecu_cal11)
		__ecu_cal12 = .;
		*(.ecu_cal12)
		__ecu_cal13 = .;
		*(.ecu_cal13)
		__ecu_cal14 = .;
		*(.ecu_cal14)
		__ecu_cal15 = .;
		*(.ecu_cal15)
		__ecu_cal16 = .;
		*(.ecu_cal16)
		__ecu_cal17 = .;
		*(.ecu_cal17)
		__ecu_cal18 = .;
		*(.ecu_cal18)
		__ecu_cal19 = .;
		*(.ecu_cal19)
		__ecu_cal20 = .;
		*(.ecu_cal20)
		__ecu_cal21 = .;
		*(.ecu_cal21)
		__ecu_cal22 = .;
		*(.ecu_cal22)
		__ecu_cal23 = .;
		*(.ecu_cal23)
		__ecu_cal24 = .;
		*(.ecu_cal24)
		__ecu_cal25 = .;
		*(.ecu_cal25)
		__ecu_cal26 = .;
		*(.ecu_cal26)
		__ecu_cal27 = .;
		*(.ecu_cal27)
		__ecu_cal28 = .;
		*(.ecu_cal28)
		__ecu_cal29 = .;
		*(.ecu_cal29)
		__ecu_cal30 = .;
		*(.ecu_cal30)
		__ecu_cal31 = .;
		*(.ecu_cal31)
		__ecu_cal32 = .;
		*(.ecu_cal32)
		__ecu_cal33 = .;
		*(.ecu_cal33)
		__ecu_cal34 = .;
		*(.ecu_cal34)
		__ecu_cal35 = .;
		*(.ecu_cal35)
		__ecu_cal36 = .;
		*(.ecu_cal36)
		__ecu_cal37 = .;
		*(.ecu_cal37)
		__ecu_cal38 = .;
		*(.ecu_cal38)
		__ecu_cal39 = .;
		*(.ecu_cal39)
		__ecu_cal40 = .;
		*(.ecu_cal40)
		__ecu_cal41 = .;
		*(.ecu_cal41)
		__ecu_cal42 = .;
		*(.ecu_cal42)
		__ecu_cal43 = .;
		*(.ecu_cal43)
		__ecu_cal44 = .;
		*(.ecu_cal44)
		__ecu_cal45 = .;
		*(.ecu_cal45)
		__ecu_cal46 = .;
		*(.ecu_cal46)
		__ecu_cal47 = .;
		*(.ecu_cal47)
		__ecu_cal48 = .;
		*(.ecu_cal48)
		__ecu_cal49 = .;
		*(.ecu_cal49)
		__ecu_cal50 = .;
		*(.ecu_cal50)
		__ecu_cal51 = .;
		*(.ecu_cal51)
		__ecu_cal52 = .;
		*(.ecu_cal52)
		__ecu_cal53 = .;
		*(.ecu_cal53)
		__ecu_cal54 = .;
		*(.ecu_cal54)
		__ecu_cal55 = .;
		*(.ecu_cal55)
		__ecu_cal56 = .;
		*(.ecu_cal56)
		__ecu_cal57 = .;
		*(.ecu_cal57)
		__ecu_cal58 = .;
		*(.ecu_cal58)
		__ecu_cal59 = .;
		*(.ecu_cal59)
		__ecu_cal60 = .;
		*(.ecu_cal60)
		__ecu_cal61 = .;
		*(.ecu_cal61)
		__ecu_cal62 = .;
		*(.ecu_cal62)
		__ecu_cal63 = .;
		*(.ecu_cal63)
		__ecu_cal_end = .;
	} : data

	__ebss = .;

	.premalloc_align . : {
		*(.premalloc_align)
	} : data

	.debug_abbrev	0 : { *(.debug_abbrev) }
	.debug_info	0 : { *(.debug_info) }
	.debug_line	0 : { *(.debug_line) }
	.debug_frame	0 : { *(.debug_frame) }
	.debug_loc	0 : { *(.debug_loc) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges	0 : { *(.debug_aranges) }
	.debug_str	0 : { *(.debug_str) }
	.debug_ranges	0 : { *(.debug_ranges) }
	/DISCARD/ : {
		*(.*) /* discard all sections not explicitly supported */
	}
}
