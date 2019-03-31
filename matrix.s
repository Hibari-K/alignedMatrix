.file "matrix.s"
.globl add_matrix_aligned
.globl add_matrix_bad
.globl add_matrix_comp


add_matrix_comp:
    li      0, 1024
    mullw   0, 0, 0
    mtctr   0
    li      8, 0

comp_loop:
    lwzx    10, 3, 8
    lwzx    11, 4, 8
    add     10, 10, 11
    stwx    10, 5, 8
    addi    8, 8, 4
    bdnz+   comp_loop

    blr



add_matrix_aligned:
    li      0, 1024    
    mulli   15, 0, 4  
    mullw   16, 15, 0 
    li      8, 0       
    
add_outer_aligned:
    li      9, 0
    mtctr   0
    
add_inner_aligned:
    add     10, 3, 8    
    add     11, 4, 8    
    lwzx    13, 10, 9   
    lwzx    14, 11, 9   
    add     13, 13, 14 
    add     12, 5, 8    
    stwx    13, 12, 9   
    addi    9, 9, 4     
    bdnz+   add_inner_aligned

    add     8, 8, 15  
    cmpw    7, 8, 16
    bne     7, add_outer_aligned
    blr


add_matrix_bad:
    li      0, 1024 
    mulli   15, 0, 4    
    mullw   16, 15, 0
    li      8, 0    
    
add_outer_bad:
    li      9, 2   
    mtctr   0
    
add_inner_bad:
    add     10, 3, 8    
    add     11, 4, 8    
    lwzx    13, 10, 9   
    lwzx    14, 11, 9   
    add     13, 13, 14 
    add     12, 5, 8    
    stwx    13, 12, 9   
    addi    9, 9, 4   
    bdnz+   add_inner_bad

    add     8, 8, 15 
    cmpw    7, 8, 16
    bne     7, add_outer_bad
    blr
