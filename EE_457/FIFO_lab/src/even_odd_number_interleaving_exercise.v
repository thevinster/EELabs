// EE457 RTL Exercises involving a FIFO
// File Name: even_odd_number_interleaving.v 
// Author: Mingyu Chang, Instructed by: Gandhi Puvvada
// Date: 10/29/2014
// Description: An array M of 16 numbers is given and we were told that there are 8 even numbers
//              and 8 odd numbers in the array but they may not be alternating.             
//              Our job is to transfer them to the array N in such way that they are alternating 
//              between odd and even, but without disturbing the relative order among the even 
//              numbers and  similarly without disturbing the relative order among the odd 
//              numbers.
//              In this design, we use one 8-location FIFO to temporarily store the excess of 
//              even or odd numbers. Note that both even and odd cannot be in excess at the same time.

`timescale 1 ns/100 ps

module even_odd_number_interleaving (clk, reset, start, ack, done, Qini, Q_first_element, Q_interleave, Qd);

input clk, reset;
input start, ack;
output done;
output Qini, Q_first_element, Q_interleave, Qd;

reg [7:0] M [0:15];
reg [7:0] N [0:15];
reg ENSF, ONSF; //even numbers stacked in the FIFO, odd numbers stacked in the FIFO; Flags to record the state of FIFO.
reg PLSB;//previous least significant bit, "1" for odd, "0" for even. It is used to record the state of the previous element in array N (Note: in N, and not in M).
reg [3:0] I, J; // indices into the arrays M and N

wire [7:0] FIFO_data_in;
reg FIFO_wen, FIFO_ren;
wire[7:0] FIFO_data_out;
wire [2:0] FIFO_depth;
wire FIFO_last_element;

wire Tr_M_to_N; // transfer_Ms_of_I_to_Ns_of_J
wire Tr_M_to_F; // transfer_Ms_of_I_to_FIFO
wire Tr_F_to_N; // transfer_from_FIFO_to_Ns_of_J

reg [3:0] state;

localparam
 
          INI = 4'b0001,
First_Element = 4'b0010,
   Interleave = 4'b0100,
         Done_S = 4'b1000;
		 
		 
//task #1: complete the FIFO instantiation. Hint: it is okay to leave certain port unconnected if it is not used.
fifo_reg_array_sc #(16,4) FIFO (   .clk(clk), 
                                  .reset(reset), 
											.data_in(FIFO_data_in), 
											.wen(FIFO_wen), 
											.ren(FIFO_ren), 
											.data_out(FIFO_data_out), 
											.depth(FIFO_depth),
											.empty(), 
											.full()
										);
								
assign FIFO_last_element = (FIFO_depth == 1);
assign done = (state == Done_S);
assign { Qd, Q_interleave, Q_first_element, Qini } = state;
assign FIFO_data_in = M[I];


//task #2: complete the conditions for data-transferring. suggestion: you may complete other tasks first, then go for this task. 
assign Tr_M_to_N  = (M[I][0] == !PLSB) && ((ENSF && M[I][0]) || (ONSF && !M[I][0])); //Hint: Based on the last number stored in N, if the current number in M is what we are looking for so far as the evenness/oddness is concerned, and 
						  // if numbers similar in evenness/oddness to the current number in M were not stacked up in the FIFO as excess numbers, we directly transfer the element of array M to array N.

assign Tr_M_to_F  =	(M[I][0] == PLSB && (PLSB == ONSF || !PLSB == ENSF)) || (FIFO_depth == 0 && M[I][0] == PLSB); //Hint: Whenever the data in FIFO similar in evenness/oddness to M[I],  or
                          // the FIFO is empty and M[I] is not the "right" data for N as the evenness/oddness is concerned, then store M[I] in FIFO.	
assign Tr_F_to_N  =	((PLSB && ENSF) || (~PLSB && ONSF)) && ~Tr_M_to_N; //Hint: A phone call suddenly interrupted me, I just forget what to write. please figure it yourself, sorry. :)

// points to ponder: 	Can all the above three conditions be true together?
//						Can all the above three conditions be false together?
//						Can two of the above three conditions be true together?


always@(posedge clk, posedge reset)
	begin
		if (reset)
			begin
			   state <= INI;
				I <= 4'bXXXX;//to avoid recirculating mux controlled by reset
				J <= 4'bXXXX;//to avoid recirculating mux controlled by reset
				ENSF <= 1'bX;//to avoid recirculating mux controlled by reset
				ONSF <= 1'bX;//to avoid recirculating mux controlled by reset
				PLSB <= 1'bX;//to avoid recirculating mux controlled by reset		
			end
		else
			begin
				case (state)
					INI: 
						begin
							I <= 4'b0000;
							J <= 4'b0000;
							ENSF <= 1'b0;
							ONSF <= 1'b0;
							
							if (start)
								state <= First_Element;
						end
					First_Element:
						begin
							N[J] <= M[I];
							I <= I + 1;
							J <= J + 1;
							if (M[I][0])
								PLSB <= 1'b1;
							else
								PLSB <= 1'b0;
								
							state <= Interleave;
						end
					Interleave:
						begin
							if ( Tr_M_to_N ) // transfer the number in M to N
								begin 
								
//task #3: There is one missing line, figure it out and fill it up. //Hint: what should we do after storing data into array N?

									N[J] <= M[I];
									I <= I + 1;
									J <= J + 1;
				    // missing line:
									PLSB <= M[I][0];
								end
							if ( Tr_M_to_F ) // transfer the M[I] to FIFO
								begin 
									I <= I + 1;
//task #4: Fill in the following condition to set ONSF and ENSF.//Hint: when should we set the odd/even state for FIFO?
									if (FIFO_depth == 0)
										begin
											if (M[I][0])
												ONSF <= 1'b1;
											else
												ENSF <= 1'b1;
										end
								end
							if ( Tr_F_to_N )
								begin 
									N[J] <= FIFO_data_out;
									J <= J + 1;
//task #5: There are two missing parts, one is the similar missing line to task #3, the other part is an "if" block. 
//Hint for the "if" part: Since here we draw data from FIFO to array N, we should take care of the "empty" situation of FIFO.
//Then should we care about when FIFO get exactly empty or when it "is going to" become empty. What should we do under such situation?
									PLSB <= FIFO_data_out[0];
									if (FIFO_last_element || FIFO_depth == 0) begin
										ENSF <= 1'b0;
										ONSF <= 1'b0;
									end
								end
//task #6: write the condition to go Done state. 								
							if (J != 15)
								state <= Done_S;
						end
					Done_S:
						begin
							if (ack)
								state <= INI;
						end
				endcase
			end
	end

always @(*) // this is OFL. One should not update FIFO_wen and FIFO_ren in the clocked block. Otherwise you will infer registers (Flip-Flops)!
	begin
		FIFO_wen = 1'b0;
		FIFO_ren = 1'b0;
		if (state == Interleave)
			begin
				if ( Tr_M_to_F ) 
						FIFO_wen = 1'b1;
				if ( Tr_F_to_N )
						FIFO_ren = 1'b1;
			end
	end
endmodule