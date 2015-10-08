// EE457 RTL Exercises
// File Name: even_odd_number_interleaving_tb.v 
// Author: Mingyu Chang
// Date: 10/29/2014
// Revised: 02/24/2015
// Note: This testbench is derived by modifying the ee457_bsort_improved_tb.v Written by Gandhi Puvvada, Prasanjeet Das


`timescale 1 ns / 100 ps

module even_odd_number_interleaving_tb;

reg Start_tb, Clk_tb, Reset_tb, ack_tb;
wire done_tb;
wire Qini_tb, Q_first_element_tb, Q_interleave_tb, Qd_tb;

reg [4*8:1] state_string; // 4 character state string for displaying state in text mode in the waveform

integer  Clk_cnt, file_results;
integer Start_clock_count, Clocks_taken;

reg [3:0] test_number   = 0;
reg [2:0] passed_number = 0;
reg [2:0] failed_number = 0;

reg [127:0] M_tb, N_tb; // M-tb is the given array. N_tb is expected array after interleaving

localparam CLK_PERIOD = 10;


even_odd_number_interleaving UUT( Clk_tb, Reset_tb, Start_tb, ack_tb, done_tb,
				                 Qini_tb, Q_first_element_tb, Q_interleave_tb, Qd_tb);
				 
				 
always @(*)
	begin
		case ({Qini_tb, Q_first_element_tb, Q_interleave_tb, Qd_tb})
			4'b1000: state_string = "INI ";
			4'b0100: state_string = "1stE";  // First_Element
			4'b0010: state_string = "InLv";  // Interleave
			4'b0001: state_string = "Done";  // Done_S state
		    default: state_string = "UNKN";
		endcase
	end

initial
  begin  : CLK_GENERATOR
    Clk_tb = 0;
    forever
       begin
	      #(CLK_PERIOD/2) Clk_tb = ~Clk_tb;
       end 
  end

initial
  begin  : RESET_GENERATOR
    Reset_tb = 1;
    #(2 * CLK_PERIOD) Reset_tb = 0;
  end

initial
  begin  : CLK_COUNTER
    Clk_cnt = 0;
	# (0.6 * CLK_PERIOD); // wait until a little after the positive edge
    forever
       begin
	      #(CLK_PERIOD) Clk_cnt <= Clk_cnt + 1;
       end 
  end

initial
  begin  : STIMULUS
	// Note: Instead of having fixed string like the one above for the name of the results file
	// (which necessitates making multiple copies of the testbench for each part), we can have
	// a common testbench and let the specific part of the core design provide us the "UUT.file_results".
	file_results = $fopen("output_results.txt", "w");
	
	test_number = 0;
	   M_tb = 128'h00_00_00_00_00_00_00_00_00_00_00_00_00_00_00_00; 
	   memory_initialization (M_tb);
      // these initializations before reset are not important
	   Start_tb = 1'b0;		// except for avoiding red color
	   ack_tb = 1'b0;
	wait (!Reset_tb);    // wait until reset is over
	@(posedge Clk_tb);   // wait for a clock
	$fdisplay (file_results, " ");
	$display  (" ");
	
// test #1 begin
	
	N_tb =        128'h69_50_71_B2_9D_86_91_3A_57_06_01_02_A9_18_85_F4; 
	M_tb =        128'h69_50_71_B2_9D_86_91_3A_57_06_01_02_A9_18_85_F4; 
	test_number = test_number + 1;
	run_test (M_tb, N_tb, test_number);

// test #1 end


// test #2 begin
	
	N_tb =        128'h61_18_37_06_55_88_11_00_07_02_09_56_01_12_25_02; 
	M_tb =        128'h61_37_18_06_55_11_88_00_07_09_02_56_01_25_12_02;  
	test_number = test_number + 1;
	run_test (M_tb, N_tb, test_number);

// test #2 end

// test #3 begin

	N_tb =        128'h00_15_02_07_02_13_08_91_62_33_22_39_56_01_60_FF;  
  	M_tb =        128'h00_02_02_15_07_13_08_91_62_33_22_56_60_39_01_FF;
	test_number = test_number + 1;
	run_test (M_tb, N_tb, test_number);

// test #3 end

// test #4 begin

	N_tb =        128'h28_51_32_33_86_63_78_11_82_89_98_33_66_2D_5C_8F; 
  	M_tb =        128'h28_51_33_32_86_78_63_11_89_82_98_66_5C_33_2D_8F;  
	test_number = test_number + 1;
	run_test (M_tb, N_tb, test_number);

// test #4 end

// test #5 begin

	N_tb =        128'h71_30_27_66_3B_50_19_98_35_82_67_56_73_42_31_20;
  	M_tb =        128'h30_66_71_27_3B_50_19_98_82_56_35_67_73_42_31_20;
	test_number = test_number + 1;
	run_test (M_tb, N_tb, test_number);

// test #5 end

// test #6 begin

	N_tb =        128'h37_56_35_82_33_30_31_28_49_26_27_34_23_22_21_10; 
  	M_tb =        128'h37_35_56_33_82_30_28_31_49_27_26_23_21_34_22_10; 
	test_number = test_number + 1;
	run_test (M_tb, N_tb, test_number);

// test #6 end

    

    if (passed_number == 3'b110)
		begin
			$fdisplay (file_results, "\n Congratulation!!!\n All tests concluded.	the number of passed tests: %d	the number of failed tests: %d", passed_number, failed_number);
			$display ("\n Congratulation!!!\n All tests concluded.	the number of passed tests: %d	the number of failed tests: %d \n Inspect the text file \"output_results.txt\" \n Current Clock Count = %0d ", passed_number, failed_number, Clk_cnt);
		end
	else
		begin
			$fdisplay (file_results, "\n Oops...\n All tests concluded.	the number of passed tests: %d	the number of failed tests: %d", passed_number, failed_number);
			$display ("\n Oops...\n All tests concluded.	the number of passed tests: %d	the number of failed tests: %d \n Inspect the text file \"output_results.txt\" \n Current Clock Count = %0d ", passed_number, failed_number, Clk_cnt);
		end
	$fclose (file_results);	 
	 // $stop;  // break in simulation. Enter interactive simulation mode
	end // STIMULUS
	


task memory_initialization; 
   input [127:0] M_local_tb;   // we could have avoided passing argument for this task as all parent variables are visible to the task.
	integer i, j;
	begin
		for (i=0; i<=15; i = i +1)
		    begin
				for (j=0; j<=7; j = j +1)
		         UUT.M[i][j]  = M_local_tb[(i*8)+j];
			end 
	end
endtask
		
task run_test;
	input [127:0] M_16x8_tb; // we could have avoided passing argument for this task as all parent variables are visible to the task.
	input [127:0] N_16x8_tb; // we could have avoided passing argument for this task as all parent variables are visible to the task.
	input [3:0]   test_numb;   // we could have avoided passing argument for this task as all parent variables are visible to the task.
	// integer Start_clock_count, Clocks_taken;
	integer dc ; // dc = display_counter
	reg [7:0] Array_element;
	reg error_found;
	begin
		// test begins
		// @(posedge Clk_tb);
		#2;
		memory_initialization (M_16x8_tb);
		Start_tb = 1;	// After a little while provide START
		@(posedge Clk_tb); 
		#5;
		Start_tb = 0;	// After a little while remove START
		Start_clock_count = Clk_cnt;
		wait (done_tb);
		#1;
		ack_tb = 1'b1;
		error_found = 1'b0;
		#4;
		Clocks_taken = Clk_cnt - Start_clock_count;
		if (done_tb == 1) 
		   begin
		    $fdisplay (file_results, "\n Test number  %d: ", test_numb);
		    $display ("\n Test number  %d: ", test_numb);
			 
			$fwrite (file_results, "	Initial memory contents:       ");
		    $write ("	Initial memory contents:       ");
			 
			for (dc=0; dc<=15; dc = dc +1)
		    begin 				
				Array_element  = {M_16x8_tb[(dc*8)+7],M_16x8_tb[(dc*8)+6],M_16x8_tb[(dc*8)+5],M_16x8_tb[(dc*8)+4],
					 M_16x8_tb[(dc*8)+3],M_16x8_tb[(dc*8)+2],M_16x8_tb[(dc*8)+1],M_16x8_tb[(dc*8)+0]};
				$fwrite (file_results, " %h ", Array_element);
				$write  (              " %h ", Array_element);
			end 
				$fdisplay (file_results, " ");
				$display  (              " ");
			
			
			
			
			$fwrite (file_results, "	Expected final memory contents:");
		    $write ("	Expected final memory contents:");
			 
			for (dc=0; dc<=15; dc = dc +1)
		    begin 				
				Array_element  = {N_16x8_tb[(dc*8)+7],N_16x8_tb[(dc*8)+6],N_16x8_tb[(dc*8)+5],N_16x8_tb[(dc*8)+4],
					 N_16x8_tb[(dc*8)+3],N_16x8_tb[(dc*8)+2],N_16x8_tb[(dc*8)+1],N_16x8_tb[(dc*8)+0]};
				$fwrite (file_results, " %h ", Array_element);
				$write  (              " %h ", Array_element);
				if (Array_element != UUT.N[dc])
					error_found = 1'b1;
			end 
				$fdisplay (file_results, " ");
				$display  (              " ");			



			
			$fwrite (file_results, "	Final memory contents:         ");
		    $write ("	Final memory contents:         ");
			 

			for (dc=0; dc<=15; dc = dc +1)
		    begin 				
				// Array_element  = {UUT.N[(dc*8)+7],UUT.N[(dc*8)+6],UUT.N[(dc*8)+5],UUT.N[(dc*8)+4],
				// 	 UUT.N[(dc*8)+3],UUT.N[(dc*8)+2],UUT.N[(dc*8)+1],UUT.N[(dc*8)+0]};
				$fwrite (file_results, " %h ", UUT.N[dc]);
				$write  (              " %h ", UUT.N[dc]);
			end 
				$fdisplay (file_results, " ");
				$display  (              " ");
			
		   end
		
		$fwrite (file_results, "	Clocks taken for this test = %0d. \n", Clocks_taken);
		$write ("	Clocks taken for this test = %0d. \n", Clocks_taken);
			if (error_found == 1'b0)
				begin
					passed_number = passed_number + 1;
					$fdisplay (file_results, "	Test number %d passed. \n", test_numb);
					$display ("	Test number %d passed. \n", test_numb);
				end
			else
				begin
					failed_number = failed_number + 1;
					$fdisplay (file_results, "	Test number %d failed. \n", test_numb);
					$display ("	Test number %d failed. \n", test_numb);
				end
		$display ("");
		@(posedge Clk_tb); // wait until the end of the end of the Done State Clock
		#1;
		ack_tb = 1'b0;
		#3;
		// test ends
	end
endtask
 
endmodule  
