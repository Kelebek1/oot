.rdata
glabel D_80B38E10
    .asciz "\n\n"
    .balign 4

glabel D_80B38E14
    .asciz "\x1b[32m☆☆☆☆☆ 不思議不思議まか不思議 	   ☆☆☆☆☆ %x\n\x1b[m"
    .balign 4

glabel D_80B38E54
    .asciz "\x1b[32m☆☆☆☆☆ Ｙｏｕ ａｒｅ Ｓｈｏｃｋ！  ☆☆☆☆☆ %d\n\x1b[m"
    .balign 4

.late_rodata
glabel jtbl_80B38ECC
.word L80B382D8
.word L80B38338
.word L80B38388
.word L80B383A4
.word L80B3855C
.word L80B38410
.word L80B38470
.word L80B384C0
.word L80B384D0
.word L80B38538
.word 0x00000000, 0x00000000, 0x00000000

.text
glabel EnWonderItem_Init
/* 0019C 80B381FC 27BDFFC8 */  addiu   $sp, $sp, 0xFFC8           ## $sp = FFFFFFC8
/* 001A0 80B38200 AFB00018 */  sw      $s0, 0x0018($sp)           
/* 001A4 80B38204 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 001A8 80B38208 AFBF001C */  sw      $ra, 0x001C($sp)           
/* 001AC 80B3820C 3C0480B4 */  lui     $a0, %hi(D_80B38E10)       ## $a0 = 80B40000
/* 001B0 80B38210 AFA5003C */  sw      $a1, 0x003C($sp)           
/* 001B4 80B38214 0C00084C */  jal     osSyncPrintf
              
/* 001B8 80B38218 24848E10 */  addiu   $a0, $a0, %lo(D_80B38E10)  ## $a0 = 80B38E10
/* 001BC 80B3821C 3C0480B4 */  lui     $a0, %hi(D_80B38E14)       ## $a0 = 80B40000
/* 001C0 80B38220 24848E14 */  addiu   $a0, $a0, %lo(D_80B38E14)  ## $a0 = 80B38E14
/* 001C4 80B38224 0C00084C */  jal     osSyncPrintf
              
/* 001C8 80B38228 8605001C */  lh      $a1, 0x001C($s0)           ## 0000001C
/* 001CC 80B3822C 8602001C */  lh      $v0, 0x001C($s0)           ## 0000001C
/* 001D0 80B38230 8E0E0004 */  lw      $t6, 0x0004($s0)           ## 00000004
/* 001D4 80B38234 2401FFFE */  addiu   $at, $zero, 0xFFFE         ## $at = FFFFFFFE
/* 001D8 80B38238 304A003F */  andi    $t2, $v0, 0x003F           ## $t2 = 00000000
/* 001DC 80B3823C A60A0162 */  sh      $t2, 0x0162($s0)           ## 00000162
/* 001E0 80B38240 86050162 */  lh      $a1, 0x0162($s0)           ## 00000162
/* 001E4 80B38244 0002C2C3 */  sra     $t8, $v0, 11               
/* 001E8 80B38248 00024183 */  sra     $t0, $v0,  6               
/* 001EC 80B3824C 01C17824 */  and     $t7, $t6, $at              
/* 001F0 80B38250 3319001F */  andi    $t9, $t8, 0x001F           ## $t9 = 00000000
/* 001F4 80B38254 3109001F */  andi    $t1, $t0, 0x001F           ## $t1 = 00000000
/* 001F8 80B38258 2401003F */  addiu   $at, $zero, 0x003F         ## $at = 0000003F
/* 001FC 80B3825C AE0F0004 */  sw      $t7, 0x0004($s0)           ## 00000004
/* 00200 80B38260 A6190154 */  sh      $t9, 0x0154($s0)           ## 00000154
/* 00204 80B38264 14A10004 */  bne     $a1, $at, .L80B38278       
/* 00208 80B38268 A6090156 */  sh      $t1, 0x0156($s0)           ## 00000156
/* 0020C 80B3826C 240BFFFF */  addiu   $t3, $zero, 0xFFFF         ## $t3 = FFFFFFFF
/* 00210 80B38270 A60B0162 */  sh      $t3, 0x0162($s0)           ## 00000162
/* 00214 80B38274 86050162 */  lh      $a1, 0x0162($s0)           ## 00000162
.L80B38278:
/* 00218 80B38278 240C0001 */  addiu   $t4, $zero, 0x0001         ## $t4 = 00000001
/* 0021C 80B3827C 04A0000D */  bltz    $a1, .L80B382B4            
/* 00220 80B38280 A20C001F */  sb      $t4, 0x001F($s0)           ## 0000001F
/* 00224 80B38284 0C00B2D0 */  jal     Flags_GetSwitch
              
/* 00228 80B38288 8FA4003C */  lw      $a0, 0x003C($sp)           
/* 0022C 80B3828C 5040000A */  beql    $v0, $zero, .L80B382B8     
/* 00230 80B38290 960D0154 */  lhu     $t5, 0x0154($s0)           ## 00000154
/* 00234 80B38294 3C0480B4 */  lui     $a0, %hi(D_80B38E54)       ## $a0 = 80B40000
/* 00238 80B38298 24848E54 */  addiu   $a0, $a0, %lo(D_80B38E54)  ## $a0 = 80B38E54
/* 0023C 80B3829C 0C00084C */  jal     osSyncPrintf
              
/* 00240 80B382A0 86050162 */  lh      $a1, 0x0162($s0)           ## 00000162
/* 00244 80B382A4 0C00B55C */  jal     Actor_Kill
              
/* 00248 80B382A8 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 0024C 80B382AC 100000AC */  beq     $zero, $zero, .L80B38560   
/* 00250 80B382B0 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B382B4:
/* 00254 80B382B4 960D0154 */  lhu     $t5, 0x0154($s0)           ## 00000154
.L80B382B8:
/* 00258 80B382B8 2DA1000A */  sltiu   $at, $t5, 0x000A           
/* 0025C 80B382BC 102000A5 */  beq     $at, $zero, .L80B38554     
/* 00260 80B382C0 000D6880 */  sll     $t5, $t5,  2               
/* 00264 80B382C4 3C0180B4 */  lui     $at, %hi(jtbl_80B38ECC)       ## $at = 80B40000
/* 00268 80B382C8 002D0821 */  addu    $at, $at, $t5              
/* 0026C 80B382CC 8C2D8ECC */  lw      $t5, %lo(jtbl_80B38ECC)($at)  
/* 00270 80B382D0 01A00008 */  jr      $t5                        
/* 00274 80B382D4 00000000 */  nop
glabel L80B382D8
/* 00278 80B382D8 86020034 */  lh      $v0, 0x0034($s0)           ## 00000034
/* 0027C 80B382DC 00001825 */  or      $v1, $zero, $zero          ## $v1 = 00000000
/* 00280 80B382E0 3C0880B4 */  lui     $t0, %hi(func_80B38570)    ## $t0 = 80B40000
/* 00284 80B382E4 304E000F */  andi    $t6, $v0, 0x000F           ## $t6 = 00000000
/* 00288 80B382E8 2841000A */  slti    $at, $v0, 0x000A           
/* 0028C 80B382EC 1420000A */  bne     $at, $zero, .L80B38318     
/* 00290 80B382F0 A60E0158 */  sh      $t6, 0x0158($s0)           ## 00000158
/* 00294 80B382F4 2401000A */  addiu   $at, $zero, 0x000A         ## $at = 0000000A
/* 00298 80B382F8 0041001A */  div     $zero, $v0, $at            
/* 0029C 80B382FC 00001812 */  mflo    $v1                        
/* 002A0 80B38300 00031C00 */  sll     $v1, $v1, 16               
/* 002A4 80B38304 00031C03 */  sra     $v1, $v1, 16               
/* 002A8 80B38308 00037880 */  sll     $t7, $v1,  2               
/* 002AC 80B3830C 01E37821 */  addu    $t7, $t7, $v1              
/* 002B0 80B38310 000F7880 */  sll     $t7, $t7,  2               
/* 002B4 80B38314 A60F016A */  sh      $t7, 0x016A($s0)           ## 0000016A
.L80B38318:
/* 002B8 80B38318 0003C080 */  sll     $t8, $v1,  2               
/* 002BC 80B3831C 0303C021 */  addu    $t8, $t8, $v1              
/* 002C0 80B38320 0018C040 */  sll     $t8, $t8,  1               
/* 002C4 80B38324 0058C823 */  subu    $t9, $v0, $t8              
/* 002C8 80B38328 25088570 */  addiu   $t0, $t0, %lo(func_80B38570) ## $t0 = 80B38570
/* 002CC 80B3832C A6190158 */  sh      $t9, 0x0158($s0)           ## 00000158
/* 002D0 80B38330 1000008A */  beq     $zero, $zero, .L80B3855C   
/* 002D4 80B38334 AE08014C */  sw      $t0, 0x014C($s0)           ## 0000014C
glabel L80B38338
/* 002D8 80B38338 86020034 */  lh      $v0, 0x0034($s0)           ## 00000034
/* 002DC 80B3833C 8E0D0024 */  lw      $t5, 0x0024($s0)           ## 00000024
/* 002E0 80B38340 3C0A80B4 */  lui     $t2, %hi(D_80B39010)       ## $t2 = 80B40000
/* 002E4 80B38344 304200FF */  andi    $v0, $v0, 0x00FF           ## $v0 = 00000000
/* 002E8 80B38348 00021400 */  sll     $v0, $v0, 16               
/* 002EC 80B3834C 00021403 */  sra     $v0, $v0, 16               
/* 002F0 80B38350 00024880 */  sll     $t1, $v0,  2               
/* 002F4 80B38354 01224823 */  subu    $t1, $t1, $v0              
/* 002F8 80B38358 00094880 */  sll     $t1, $t1,  2               
/* 002FC 80B3835C 254A9010 */  addiu   $t2, $t2, %lo(D_80B39010)  ## $t2 = 80B39010
/* 00300 80B38360 012A5821 */  addu    $t3, $t1, $t2              
/* 00304 80B38364 AD6D0000 */  sw      $t5, 0x0000($t3)           ## 00000000
/* 00308 80B38368 8E0C0028 */  lw      $t4, 0x0028($s0)           ## 00000028
/* 0030C 80B3836C 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 00310 80B38370 AD6C0004 */  sw      $t4, 0x0004($t3)           ## 00000004
/* 00314 80B38374 8E0D002C */  lw      $t5, 0x002C($s0)           ## 0000002C
/* 00318 80B38378 0C00B55C */  jal     Actor_Kill
              
/* 0031C 80B3837C AD6D0008 */  sw      $t5, 0x0008($t3)           ## 00000008
/* 00320 80B38380 10000077 */  beq     $zero, $zero, .L80B38560   
/* 00324 80B38384 8FBF001C */  lw      $ra, 0x001C($sp)           
glabel L80B38388
/* 00328 80B38388 860E0034 */  lh      $t6, 0x0034($s0)           ## 00000034
/* 0032C 80B3838C 3C1880B4 */  lui     $t8, %hi(func_80B38788)    ## $t8 = 80B40000
/* 00330 80B38390 27188788 */  addiu   $t8, $t8, %lo(func_80B38788) ## $t8 = 80B38788
/* 00334 80B38394 31CF00FF */  andi    $t7, $t6, 0x00FF           ## $t7 = 00000000
/* 00338 80B38398 A60F015A */  sh      $t7, 0x015A($s0)           ## 0000015A
/* 0033C 80B3839C 1000006F */  beq     $zero, $zero, .L80B3855C   
/* 00340 80B383A0 AE18014C */  sw      $t8, 0x014C($s0)           ## 0000014C
glabel L80B383A4
/* 00344 80B383A4 86190034 */  lh      $t9, 0x0034($s0)           ## 00000034
/* 00348 80B383A8 26050180 */  addiu   $a1, $s0, 0x0180           ## $a1 = 00000180
/* 0034C 80B383AC AFA50024 */  sw      $a1, 0x0024($sp)           
/* 00350 80B383B0 332800FF */  andi    $t0, $t9, 0x00FF           ## $t0 = 00000000
/* 00354 80B383B4 A7A80032 */  sh      $t0, 0x0032($sp)           
/* 00358 80B383B8 0C0170D9 */  jal     Collider_InitCylinder
              
/* 0035C 80B383BC 8FA4003C */  lw      $a0, 0x003C($sp)           
/* 00360 80B383C0 3C0780B4 */  lui     $a3, %hi(D_80B38D40)       ## $a3 = 80B40000
/* 00364 80B383C4 8FA50024 */  lw      $a1, 0x0024($sp)           
/* 00368 80B383C8 24E78D40 */  addiu   $a3, $a3, %lo(D_80B38D40)  ## $a3 = 80B38D40
/* 0036C 80B383CC 8FA4003C */  lw      $a0, 0x003C($sp)           
/* 00370 80B383D0 0C01712B */  jal     Collider_SetCylinder
              
/* 00374 80B383D4 02003025 */  or      $a2, $s0, $zero            ## $a2 = 00000000
/* 00378 80B383D8 87A90032 */  lh      $t1, 0x0032($sp)           
/* 0037C 80B383DC 3C0B80B4 */  lui     $t3, %hi(D_80B38DA4)       ## $t3 = 80B40000
/* 00380 80B383E0 3C0E80B4 */  lui     $t6, %hi(func_80B387F0)    ## $t6 = 80B40000
/* 00384 80B383E4 00095080 */  sll     $t2, $t1,  2               
/* 00388 80B383E8 016A5821 */  addu    $t3, $t3, $t2              
/* 0038C 80B383EC 8D6B8DA4 */  lw      $t3, %lo(D_80B38DA4)($t3)  
/* 00390 80B383F0 240C0014 */  addiu   $t4, $zero, 0x0014         ## $t4 = 00000014
/* 00394 80B383F4 240D001E */  addiu   $t5, $zero, 0x001E         ## $t5 = 0000001E
/* 00398 80B383F8 25CE87F0 */  addiu   $t6, $t6, %lo(func_80B387F0) ## $t6 = 80B387F0
/* 0039C 80B383FC A60C01C0 */  sh      $t4, 0x01C0($s0)           ## 000001C0
/* 003A0 80B38400 A60D01C2 */  sh      $t5, 0x01C2($s0)           ## 000001C2
/* 003A4 80B38404 AE0E014C */  sw      $t6, 0x014C($s0)           ## 0000014C
/* 003A8 80B38408 10000054 */  beq     $zero, $zero, .L80B3855C   
/* 003AC 80B3840C AE0B01A0 */  sw      $t3, 0x01A0($s0)           ## 000001A0
glabel L80B38410
/* 003B0 80B38410 86020034 */  lh      $v0, 0x0034($s0)           ## 00000034
/* 003B4 80B38414 00001825 */  or      $v1, $zero, $zero          ## $v1 = 00000000
/* 003B8 80B38418 3C0980B4 */  lui     $t1, %hi(func_80B388AC)    ## $t1 = 80B40000
/* 003BC 80B3841C 304F000F */  andi    $t7, $v0, 0x000F           ## $t7 = 00000000
/* 003C0 80B38420 2841000A */  slti    $at, $v0, 0x000A           
/* 003C4 80B38424 1420000A */  bne     $at, $zero, .L80B38450     
/* 003C8 80B38428 A60F0158 */  sh      $t7, 0x0158($s0)           ## 00000158
/* 003CC 80B3842C 2401000A */  addiu   $at, $zero, 0x000A         ## $at = 0000000A
/* 003D0 80B38430 0041001A */  div     $zero, $v0, $at            
/* 003D4 80B38434 00001812 */  mflo    $v1                        
/* 003D8 80B38438 00031C00 */  sll     $v1, $v1, 16               
/* 003DC 80B3843C 00031C03 */  sra     $v1, $v1, 16               
/* 003E0 80B38440 0003C080 */  sll     $t8, $v1,  2               
/* 003E4 80B38444 0303C021 */  addu    $t8, $t8, $v1              
/* 003E8 80B38448 0018C080 */  sll     $t8, $t8,  2               
/* 003EC 80B3844C A618016A */  sh      $t8, 0x016A($s0)           ## 0000016A
.L80B38450:
/* 003F0 80B38450 0003C880 */  sll     $t9, $v1,  2               
/* 003F4 80B38454 0323C821 */  addu    $t9, $t9, $v1              
/* 003F8 80B38458 0019C840 */  sll     $t9, $t9,  1               
/* 003FC 80B3845C 00594023 */  subu    $t0, $v0, $t9              
/* 00400 80B38460 252988AC */  addiu   $t1, $t1, %lo(func_80B388AC) ## $t1 = 80B388AC
/* 00404 80B38464 A6080158 */  sh      $t0, 0x0158($s0)           ## 00000158
/* 00408 80B38468 1000003C */  beq     $zero, $zero, .L80B3855C   
/* 0040C 80B3846C AE09014C */  sw      $t1, 0x014C($s0)           ## 0000014C
glabel L80B38470
/* 00410 80B38470 86020034 */  lh      $v0, 0x0034($s0)           ## 00000034
/* 00414 80B38474 8E0E0024 */  lw      $t6, 0x0024($s0)           ## 00000024
/* 00418 80B38478 3C0B80B4 */  lui     $t3, %hi(D_80B39080)       ## $t3 = 80B40000
/* 0041C 80B3847C 304200FF */  andi    $v0, $v0, 0x00FF           ## $v0 = 00000000
/* 00420 80B38480 00021400 */  sll     $v0, $v0, 16               
/* 00424 80B38484 00021403 */  sra     $v0, $v0, 16               
/* 00428 80B38488 00025080 */  sll     $t2, $v0,  2               
/* 0042C 80B3848C 01425023 */  subu    $t2, $t2, $v0              
/* 00430 80B38490 000A5080 */  sll     $t2, $t2,  2               
/* 00434 80B38494 256B9080 */  addiu   $t3, $t3, %lo(D_80B39080)  ## $t3 = 80B39080
/* 00438 80B38498 014B6021 */  addu    $t4, $t2, $t3              
/* 0043C 80B3849C AD8E0000 */  sw      $t6, 0x0000($t4)           ## 00000014
/* 00440 80B384A0 8E0D0028 */  lw      $t5, 0x0028($s0)           ## 00000028
/* 00444 80B384A4 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 00448 80B384A8 AD8D0004 */  sw      $t5, 0x0004($t4)           ## 00000018
/* 0044C 80B384AC 8E0E002C */  lw      $t6, 0x002C($s0)           ## 0000002C
/* 00450 80B384B0 0C00B55C */  jal     Actor_Kill
              
/* 00454 80B384B4 AD8E0008 */  sw      $t6, 0x0008($t4)           ## 0000001C
/* 00458 80B384B8 10000029 */  beq     $zero, $zero, .L80B38560   
/* 0045C 80B384BC 8FBF001C */  lw      $ra, 0x001C($sp)           
glabel L80B384C0
/* 00460 80B384C0 3C0F80B4 */  lui     $t7, %hi(func_80B38824)    ## $t7 = 80B40000
/* 00464 80B384C4 25EF8824 */  addiu   $t7, $t7, %lo(func_80B38824) ## $t7 = 80B38824
/* 00468 80B384C8 10000024 */  beq     $zero, $zero, .L80B3855C   
/* 0046C 80B384CC AE0F014C */  sw      $t7, 0x014C($s0)           ## 0000014C
glabel L80B384D0
/* 00470 80B384D0 26050180 */  addiu   $a1, $s0, 0x0180           ## $a1 = 00000180
/* 00474 80B384D4 AFA50024 */  sw      $a1, 0x0024($sp)           
/* 00478 80B384D8 0C0170D9 */  jal     Collider_InitCylinder
              
/* 0047C 80B384DC 8FA4003C */  lw      $a0, 0x003C($sp)           
/* 00480 80B384E0 3C0780B4 */  lui     $a3, %hi(D_80B38D40)       ## $a3 = 80B40000
/* 00484 80B384E4 8FA50024 */  lw      $a1, 0x0024($sp)           
/* 00488 80B384E8 24E78D40 */  addiu   $a3, $a3, %lo(D_80B38D40)  ## $a3 = 80B38D40
/* 0048C 80B384EC 8FA4003C */  lw      $a0, 0x003C($sp)           
/* 00490 80B384F0 0C01712B */  jal     Collider_SetCylinder
              
/* 00494 80B384F4 02003025 */  or      $a2, $s0, $zero            ## $a2 = 00000000
/* 00498 80B384F8 8E080024 */  lw      $t0, 0x0024($s0)           ## 00000024
/* 0049C 80B384FC 8E190028 */  lw      $t9, 0x0028($s0)           ## 00000028
/* 004A0 80B38500 3C0B80B4 */  lui     $t3, %hi(func_80B38AD8)    ## $t3 = 80B40000
/* 004A4 80B38504 AE08016C */  sw      $t0, 0x016C($s0)           ## 0000016C
/* 004A8 80B38508 8E08002C */  lw      $t0, 0x002C($s0)           ## 0000002C
/* 004AC 80B3850C 24180004 */  addiu   $t8, $zero, 0x0004         ## $t8 = 00000004
/* 004B0 80B38510 24090023 */  addiu   $t1, $zero, 0x0023         ## $t1 = 00000023
/* 004B4 80B38514 240A004B */  addiu   $t2, $zero, 0x004B         ## $t2 = 0000004B
/* 004B8 80B38518 256B8AD8 */  addiu   $t3, $t3, %lo(func_80B38AD8) ## $t3 = 80B38AD8
/* 004BC 80B3851C AE1801A0 */  sw      $t8, 0x01A0($s0)           ## 000001A0
/* 004C0 80B38520 A60901C0 */  sh      $t1, 0x01C0($s0)           ## 000001C0
/* 004C4 80B38524 A60A01C2 */  sh      $t2, 0x01C2($s0)           ## 000001C2
/* 004C8 80B38528 AE0B014C */  sw      $t3, 0x014C($s0)           ## 0000014C
/* 004CC 80B3852C AE190170 */  sw      $t9, 0x0170($s0)           ## 00000170
/* 004D0 80B38530 1000000A */  beq     $zero, $zero, .L80B3855C   
/* 004D4 80B38534 AE080174 */  sw      $t0, 0x0174($s0)           ## 00000174
glabel L80B38538
/* 004D8 80B38538 860C0034 */  lh      $t4, 0x0034($s0)           ## 00000034
/* 004DC 80B3853C 3C0E80B4 */  lui     $t6, %hi(func_80B38B78)    ## $t6 = 80B40000
/* 004E0 80B38540 25CE8B78 */  addiu   $t6, $t6, %lo(func_80B38B78) ## $t6 = 80B38B78
/* 004E4 80B38544 318D00FF */  andi    $t5, $t4, 0x00FF           ## $t5 = 00000000
/* 004E8 80B38548 A60D015A */  sh      $t5, 0x015A($s0)           ## 0000015A
/* 004EC 80B3854C 10000003 */  beq     $zero, $zero, .L80B3855C   
/* 004F0 80B38550 AE0E014C */  sw      $t6, 0x014C($s0)           ## 0000014C
.L80B38554:
/* 004F4 80B38554 0C00B55C */  jal     Actor_Kill
              
/* 004F8 80B38558 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
glabel L80B3855C
.L80B3855C:
/* 004FC 80B3855C 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B38560:
/* 00500 80B38560 8FB00018 */  lw      $s0, 0x0018($sp)           
/* 00504 80B38564 27BD0038 */  addiu   $sp, $sp, 0x0038           ## $sp = 00000000
/* 00508 80B38568 03E00008 */  jr      $ra                        
/* 0050C 80B3856C 00000000 */  nop
