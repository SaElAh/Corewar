.name "Geralt of Rivia aka The Witcher"
.comment "Toss a coin to your Witcher, oh valley of plenty"

test:		ld 4294967295, r2 
			ld 4294967295, r3
			ld 4294967295, r4
			ld 4294967295, r5

label00:	sti r1, %:live, %1
			sti r5, r6, %200
			add r5, r6, r6
			and r15, r15,r15

label01:	st r1, 0
			live %0
			sti r2, r3, %200
			add r2, r3, r3
			and r16, r16, r16

live:		live %1
			zjmp %:test
#
