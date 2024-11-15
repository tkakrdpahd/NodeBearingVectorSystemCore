/**
 * NormalizedFixedPoint.h
 * 
 * Equations:
 * Equ(1): x_"norm" =(2×(x_"original" -"min" ))/("max" -"min" )-1
 * Equ(2): x_"fixed" =((x_"norm" +1)/2)×(2^64-1)
 * Equ(3): x_"norm" =2×x_"fixed" /(2^64-1)-1
 * Equ(4): x_"original" =((x_"norm" +1)/2)×("max" -"min" )+"min" 
 */