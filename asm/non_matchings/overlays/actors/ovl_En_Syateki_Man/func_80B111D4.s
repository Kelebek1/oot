.rdata
glabel D_80B11748
    .asciz "\x1b[32m☆☆☆☆☆ 正常終了 ☆☆☆☆☆ \n\x1b[m"
    .balign 4

.text
glabel func_80B111D4
/* 00964 80B111D4 27BDFFE0 */  addiu   $sp, $sp, 0xFFE0           ## $sp = FFFFFFE0
/* 00968 80B111D8 AFB00018 */  sw      $s0, 0x0018($sp)           
/* 0096C 80B111DC 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 00970 80B111E0 AFBF001C */  sw      $ra, 0x001C($sp)           
/* 00974 80B111E4 AFA50024 */  sw      $a1, 0x0024($sp)           
/* 00978 80B111E8 0C02927F */  jal     SkelAnime_FrameUpdateMatrix
              
/* 0097C 80B111EC 2484014C */  addiu   $a0, $a0, 0x014C           ## $a0 = 0000014C
/* 00980 80B111F0 8FA40024 */  lw      $a0, 0x0024($sp)           
/* 00984 80B111F4 0C042F6F */  jal     func_8010BDBC              
/* 00988 80B111F8 248420D8 */  addiu   $a0, $a0, 0x20D8           ## $a0 = 000020D8
/* 0098C 80B111FC 24010006 */  addiu   $at, $zero, 0x0006         ## $at = 00000006
/* 00990 80B11200 54410023 */  bnel    $v0, $at, .L80B11290       
/* 00994 80B11204 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 00998 80B11208 0C041AF2 */  jal     func_80106BC8              
/* 0099C 80B1120C 8FA40024 */  lw      $a0, 0x0024($sp)           
/* 009A0 80B11210 1040001E */  beq     $v0, $zero, .L80B1128C     
/* 009A4 80B11214 3C0480B1 */  lui     $a0, %hi(D_80B11748)       ## $a0 = 80B10000
/* 009A8 80B11218 0C00084C */  jal     osSyncPrintf
              
/* 009AC 80B1121C 24841748 */  addiu   $a0, $a0, %lo(D_80B11748)  ## $a0 = 80B11748
/* 009B0 80B11220 3C038016 */  lui     $v1, %hi(gSaveContext)
/* 009B4 80B11224 2463E660 */  addiu   $v1, %lo(gSaveContext)
/* 009B8 80B11228 8C6E0004 */  lw      $t6, 0x0004($v1)           ## 8015E664
/* 009BC 80B1122C 3C0C80B1 */  lui     $t4, %hi(func_80B109DC)    ## $t4 = 80B10000
/* 009C0 80B11230 258C09DC */  addiu   $t4, $t4, %lo(func_80B109DC) ## $t4 = 80B109DC
/* 009C4 80B11234 51C00006 */  beql    $t6, $zero, .L80B11250     
/* 009C8 80B11238 8E020218 */  lw      $v0, 0x0218($s0)           ## 00000218
/* 009CC 80B1123C 946F0EF0 */  lhu     $t7, 0x0EF0($v1)           ## 8015F550
/* 009D0 80B11240 35F82000 */  ori     $t8, $t7, 0x2000           ## $t8 = 00002000
/* 009D4 80B11244 1000000A */  beq     $zero, $zero, .L80B11270   
/* 009D8 80B11248 A4780EF0 */  sh      $t8, 0x0EF0($v1)           ## 8015F550
/* 009DC 80B1124C 8E020218 */  lw      $v0, 0x0218($s0)           ## 00000218
.L80B11250:
/* 009E0 80B11250 24010030 */  addiu   $at, $zero, 0x0030         ## $at = 00000030
/* 009E4 80B11254 10410003 */  beq     $v0, $at, .L80B11264       
/* 009E8 80B11258 24010031 */  addiu   $at, $zero, 0x0031         ## $at = 00000031
/* 009EC 80B1125C 54410005 */  bnel    $v0, $at, .L80B11274       
/* 009F0 80B11260 8E0A0004 */  lw      $t2, 0x0004($s0)           ## 00000004
.L80B11264:
/* 009F4 80B11264 94790EF0 */  lhu     $t9, 0x0EF0($v1)           ## 8015F550
/* 009F8 80B11268 37284000 */  ori     $t0, $t9, 0x4000           ## $t0 = 00004000
/* 009FC 80B1126C A4680EF0 */  sh      $t0, 0x0EF0($v1)           ## 8015F550
.L80B11270:
/* 00A00 80B11270 8E0A0004 */  lw      $t2, 0x0004($s0)           ## 00000004
.L80B11274:
/* 00A04 80B11274 8E090220 */  lw      $t1, 0x0220($s0)           ## 00000220
/* 00A08 80B11278 A6000214 */  sh      $zero, 0x0214($s0)         ## 00000214
/* 00A0C 80B1127C 354B0001 */  ori     $t3, $t2, 0x0001           ## $t3 = 00000001
/* 00A10 80B11280 AE0B0004 */  sw      $t3, 0x0004($s0)           ## 00000004
/* 00A14 80B11284 AE0C01FC */  sw      $t4, 0x01FC($s0)           ## 000001FC
/* 00A18 80B11288 AE090118 */  sw      $t1, 0x0118($s0)           ## 00000118
.L80B1128C:
/* 00A1C 80B1128C 8FBF001C */  lw      $ra, 0x001C($sp)           
.L80B11290:
/* 00A20 80B11290 8FB00018 */  lw      $s0, 0x0018($sp)           
/* 00A24 80B11294 27BD0020 */  addiu   $sp, $sp, 0x0020           ## $sp = 00000000
/* 00A28 80B11298 03E00008 */  jr      $ra                        
/* 00A2C 80B1129C 00000000 */  nop
