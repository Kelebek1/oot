.late_rodata
glabel D_80A061D8
    .float 0.1

glabel D_80A061DC
    .float 0.2

glabel D_80A061E0
    .float 0.008

glabel D_80A061E4
    .float 0.05

.text
glabel func_80A03610
/* 019E0 80A03610 27BDFFD0 */  addiu   $sp, $sp, 0xFFD0           ## $sp = FFFFFFD0
/* 019E4 80A03614 AFBF0024 */  sw      $ra, 0x0024($sp)           
/* 019E8 80A03618 AFB00020 */  sw      $s0, 0x0020($sp)           
/* 019EC 80A0361C AFA50034 */  sw      $a1, 0x0034($sp)           
/* 019F0 80A03620 8CAF1C44 */  lw      $t7, 0x1C44($a1)           ## 00001C44
/* 019F4 80A03624 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 019F8 80A03628 2484014C */  addiu   $a0, $a0, 0x014C           ## $a0 = 0000014C
/* 019FC 80A0362C 0C02927F */  jal     SkelAnime_FrameUpdateMatrix
              
/* 01A00 80A03630 AFAF002C */  sw      $t7, 0x002C($sp)           
/* 01A04 80A03634 3C013F80 */  lui     $at, 0x3F80                ## $at = 3F800000
/* 01A08 80A03638 44812000 */  mtc1    $at, $f4                   ## $f4 = 1.00
/* 01A0C 80A0363C 3C063DCC */  lui     $a2, 0x3DCC                ## $a2 = 3DCC0000
/* 01A10 80A03640 34C6CCCD */  ori     $a2, $a2, 0xCCCD           ## $a2 = 3DCCCCCD
/* 01A14 80A03644 260402B8 */  addiu   $a0, $s0, 0x02B8           ## $a0 = 000002B8
/* 01A18 80A03648 3C0541F0 */  lui     $a1, 0x41F0                ## $a1 = 41F00000
/* 01A1C 80A0364C 3C074080 */  lui     $a3, 0x4080                ## $a3 = 40800000
/* 01A20 80A03650 0C01E0C4 */  jal     Math_SmoothScaleMaxMinF
              
/* 01A24 80A03654 E7A40010 */  swc1    $f4, 0x0010($sp)           
/* 01A28 80A03658 0C01DE0D */  jal     Math_Coss
              ## coss?
/* 01A2C 80A0365C 860402AC */  lh      $a0, 0x02AC($s0)           ## 000002AC
/* 01A30 80A03660 C60602B8 */  lwc1    $f6, 0x02B8($s0)           ## 000002B8
/* 01A34 80A03664 C60202B4 */  lwc1    $f2, 0x02B4($s0)           ## 000002B4
/* 01A38 80A03668 C60A0290 */  lwc1    $f10, 0x0290($s0)          ## 00000290
/* 01A3C 80A0366C 46060202 */  mul.s   $f8, $f0, $f6              
/* 01A40 80A03670 860302AA */  lh      $v1, 0x02AA($s0)           ## 000002AA
/* 01A44 80A03674 46025400 */  add.s   $f16, $f10, $f2            
/* 01A48 80A03678 3C014000 */  lui     $at, 0x4000                ## $at = 40000000
/* 01A4C 80A0367C 00601025 */  or      $v0, $v1, $zero            ## $v0 = 00000000
/* 01A50 80A03680 E6100290 */  swc1    $f16, 0x0290($s0)          ## 00000290
/* 01A54 80A03684 10600006 */  beq     $v1, $zero, .L80A036A0     
/* 01A58 80A03688 E608028C */  swc1    $f8, 0x028C($s0)           ## 0000028C
/* 01A5C 80A0368C 24010001 */  addiu   $at, $zero, 0x0001         ## $at = 00000001
/* 01A60 80A03690 50410011 */  beql    $v0, $at, .L80A036D8       
/* 01A64 80A03694 3C01BF80 */  lui     $at, 0xBF80                ## $at = BF800000
/* 01A68 80A03698 10000018 */  beq     $zero, $zero, .L80A036FC   
/* 01A6C 80A0369C 00000000 */  nop
.L80A036A0:
/* 01A70 80A036A0 44819000 */  mtc1    $at, $f18                  ## $f18 = -1.00
/* 01A74 80A036A4 3C0180A0 */  lui     $at, %hi(D_80A061D8)       ## $at = 80A00000
/* 01A78 80A036A8 24780001 */  addiu   $t8, $v1, 0x0001           ## $t8 = 00000001
/* 01A7C 80A036AC 4612103C */  c.lt.s  $f2, $f18                  
/* 01A80 80A036B0 00000000 */  nop
/* 01A84 80A036B4 45000005 */  bc1f    .L80A036CC                 
/* 01A88 80A036B8 00000000 */  nop
/* 01A8C 80A036BC C42461D8 */  lwc1    $f4, %lo(D_80A061D8)($at)  
/* 01A90 80A036C0 46041180 */  add.s   $f6, $f2, $f4              
/* 01A94 80A036C4 1000000D */  beq     $zero, $zero, .L80A036FC   
/* 01A98 80A036C8 E60602B4 */  swc1    $f6, 0x02B4($s0)           ## 000002B4
.L80A036CC:
/* 01A9C 80A036CC 1000000B */  beq     $zero, $zero, .L80A036FC   
/* 01AA0 80A036D0 A61802AA */  sh      $t8, 0x02AA($s0)           ## 000002AA
/* 01AA4 80A036D4 3C01BF80 */  lui     $at, 0xBF80                ## $at = BF800000
.L80A036D8:
/* 01AA8 80A036D8 44814000 */  mtc1    $at, $f8                   ## $f8 = -1.00
/* 01AAC 80A036DC 3C0180A0 */  lui     $at, %hi(D_80A061DC)       ## $at = 80A00000
/* 01AB0 80A036E0 4602403C */  c.lt.s  $f8, $f2                   
/* 01AB4 80A036E4 00000000 */  nop
/* 01AB8 80A036E8 45000004 */  bc1f    .L80A036FC                 
/* 01ABC 80A036EC 00000000 */  nop
/* 01AC0 80A036F0 C42A61DC */  lwc1    $f10, %lo(D_80A061DC)($at) 
/* 01AC4 80A036F4 460A1401 */  sub.s   $f16, $f2, $f10            
/* 01AC8 80A036F8 E61002B4 */  swc1    $f16, 0x02B4($s0)          ## 000002B4
.L80A036FC:
/* 01ACC 80A036FC 0C01DE1C */  jal     Math_Sins
              ## sins?
/* 01AD0 80A03700 860402AC */  lh      $a0, 0x02AC($s0)           ## 000002AC
/* 01AD4 80A03704 C61202B8 */  lwc1    $f18, 0x02B8($s0)          ## 000002B8
/* 01AD8 80A03708 861902AC */  lh      $t9, 0x02AC($s0)           ## 000002AC
/* 01ADC 80A0370C 860802B0 */  lh      $t0, 0x02B0($s0)           ## 000002B0
/* 01AE0 80A03710 46009107 */  neg.s   $f4, $f18                  
/* 01AE4 80A03714 3C063E4C */  lui     $a2, 0x3E4C                ## $a2 = 3E4C0000
/* 01AE8 80A03718 46040182 */  mul.s   $f6, $f0, $f4              
/* 01AEC 80A0371C 03284821 */  addu    $t1, $t9, $t0              
/* 01AF0 80A03720 A60902AC */  sh      $t1, 0x02AC($s0)           ## 000002AC
/* 01AF4 80A03724 34C6CCCD */  ori     $a2, $a2, 0xCCCD           ## $a2 = 3E4CCCCD
/* 01AF8 80A03728 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01AFC 80A0372C E6060294 */  swc1    $f6, 0x0294($s0)           ## 00000294
/* 01B00 80A03730 8FA5002C */  lw      $a1, 0x002C($sp)           
/* 01B04 80A03734 0C280B26 */  jal     func_80A02C98              
/* 01B08 80A03738 24A50024 */  addiu   $a1, $a1, 0x0024           ## $a1 = 00000024
/* 01B0C 80A0373C 44801000 */  mtc1    $zero, $f2                 ## $f2 = 0.00
/* 01B10 80A03740 C60802B4 */  lwc1    $f8, 0x02B4($s0)           ## 000002B4
/* 01B14 80A03744 3C0141A0 */  lui     $at, 0x41A0                ## $at = 41A00000
/* 01B18 80A03748 4602403C */  c.lt.s  $f8, $f2                   
/* 01B1C 80A0374C 00000000 */  nop
/* 01B20 80A03750 45020016 */  bc1fl   .L80A037AC                 
/* 01B24 80A03754 3C01C120 */  lui     $at, 0xC120                ## $at = C1200000
/* 01B28 80A03758 C6000290 */  lwc1    $f0, 0x0290($s0)           ## 00000290
/* 01B2C 80A0375C 44815000 */  mtc1    $at, $f10                  ## $f10 = -10.00
/* 01B30 80A03760 00000000 */  nop
/* 01B34 80A03764 460A003C */  c.lt.s  $f0, $f10                  
/* 01B38 80A03768 00000000 */  nop
/* 01B3C 80A0376C 4502000F */  bc1fl   .L80A037AC                 
/* 01B40 80A03770 3C01C120 */  lui     $at, 0xC120                ## $at = C1200000
/* 01B44 80A03774 4600103C */  c.lt.s  $f2, $f0                   
/* 01B48 80A03778 3C0180A0 */  lui     $at, %hi(D_80A061E0)       ## $at = 80A00000
/* 01B4C 80A0377C 4502000B */  bc1fl   .L80A037AC                 
/* 01B50 80A03780 3C01C120 */  lui     $at, 0xC120                ## $at = C1200000
/* 01B54 80A03784 C43061E0 */  lwc1    $f16, %lo(D_80A061E0)($at) 
/* 01B58 80A03788 3C0180A0 */  lui     $at, %hi(D_80A061E4)       ## $at = 80A00000
/* 01B5C 80A0378C C42461E4 */  lwc1    $f4, %lo(D_80A061E4)($at)  
/* 01B60 80A03790 46100482 */  mul.s   $f18, $f0, $f16            
/* 01B64 80A03794 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01B68 80A03798 46049182 */  mul.s   $f6, $f18, $f4             
/* 01B6C 80A0379C 44053000 */  mfc1    $a1, $f6                   
/* 01B70 80A037A0 0C00B58B */  jal     Actor_SetScale
              
/* 01B74 80A037A4 00000000 */  nop
/* 01B78 80A037A8 3C01C120 */  lui     $at, 0xC120                ## $at = C1200000
.L80A037AC:
/* 01B7C 80A037AC 44815000 */  mtc1    $at, $f10                  ## $f10 = -10.00
/* 01B80 80A037B0 C6080290 */  lwc1    $f8, 0x0290($s0)           ## 00000290
/* 01B84 80A037B4 460A403C */  c.lt.s  $f8, $f10                  
/* 01B88 80A037B8 00000000 */  nop
/* 01B8C 80A037BC 45020006 */  bc1fl   .L80A037D8                 
/* 01B90 80A037C0 C60C0064 */  lwc1    $f12, 0x0064($s0)          ## 00000064
/* 01B94 80A037C4 0C00B55C */  jal     Actor_Kill
              
/* 01B98 80A037C8 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01B9C 80A037CC 1000000D */  beq     $zero, $zero, .L80A03804   
/* 01BA0 80A037D0 8FBF0024 */  lw      $ra, 0x0024($sp)           
/* 01BA4 80A037D4 C60C0064 */  lwc1    $f12, 0x0064($s0)          ## 00000064
.L80A037D8:
/* 01BA8 80A037D8 0C034199 */  jal     atan2s
              
/* 01BAC 80A037DC C60E005C */  lwc1    $f14, 0x005C($s0)          ## 0000005C
/* 01BB0 80A037E0 A60202BC */  sh      $v0, 0x02BC($s0)           ## 000002BC
/* 01BB4 80A037E4 8FA50034 */  lw      $a1, 0x0034($sp)           
/* 01BB8 80A037E8 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01BBC 80A037EC 0C28126D */  jal     func_80A049B4              
/* 01BC0 80A037F0 24060020 */  addiu   $a2, $zero, 0x0020         ## $a2 = 00000020
/* 01BC4 80A037F4 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 01BC8 80A037F8 0C00BE0A */  jal     Audio_PlayActorSound2
              
/* 01BCC 80A037FC 240520A8 */  addiu   $a1, $zero, 0x20A8         ## $a1 = 000020A8
/* 01BD0 80A03800 8FBF0024 */  lw      $ra, 0x0024($sp)           
.L80A03804:
/* 01BD4 80A03804 8FB00020 */  lw      $s0, 0x0020($sp)           
/* 01BD8 80A03808 27BD0030 */  addiu   $sp, $sp, 0x0030           ## $sp = 00000000
/* 01BDC 80A0380C 03E00008 */  jr      $ra                        
/* 01BE0 80A03810 00000000 */  nop
