set key right box
set style data lines
set style line 1 lc rgb "blue" lw 2
set style line 2 lc rgb "red" lw 2

set terminal png
set yrange [-2:2]

do for [t=0:ARG2] {
   fname_out = sprintf("animationFrames/t%d.png", t)
   set output fname_out
   plot "psi.txt" every ::ARG1*t::ARG1*(t+1)-1 using 1:2 title "Re" lc rgb "blue" lw 2,\
        "psi.txt" every ::ARG1*t::ARG1*(t+1)-1 using 1:3 title "Im" lc rgb "red" lw 2,\
	"Vx.txt"  every ::::ARG1            using 1:2 title "V(x)" lc rgb "orange" lw 2
}
