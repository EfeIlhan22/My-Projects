.data 
.text
.globl main

main:
la  $t9,268500992

addi $t1,$t0,15
addi $t2,$t0,24
add $t3,$t1,$t2
sub $t4,$t1,$t2
and $t5,$t1,$t2
or $t6,$t1,$t2
xor $t7,$t1,$t2


sw $t1,0($t9)
sw $t2,4($t9)
sw $t3,8($t9)
sw $t4,12($t9)
sw $t5,16($t9)
sw $t6,20($t9)
sw $t7,24($t9)
