// Pong VGA game
// (c) fpga4fun.com

module pong(ClkPort, vga_h_sync, vga_v_sync, vga_R, vga_G, vga_B,
				St_ce_bar, St_rp_bar, Mt_ce_bar, Mt_St_oe_bar, Mt_St_we_bar, Sw0, Sw1,
				MISO, SS, MOSI, SCLK, MISO2, SS2, MOSI2, SCLK2,
				An0, An1, An2, An3, Ca, Cb, Cc, Cd, Ce, Cf, Cg, Dp);
input ClkPort, Sw0, Sw1;
			input MISO;					// Master In Slave Out, Pin 3, Port JA
			output SS;					// Slave Select, Pin 1, Port JA
			output MOSI;				// Master Out Slave In, Pin 2, Port JA
			output SCLK;				// Serial Clock, Pin 4, Port JA
			input MISO2;					// Master In Slave Out, Pin 3, Port JB
			output SS2;					// Slave Select, Pin 1, Port JB
			output MOSI2;				// Master Out Slave In, Pin 2, Port JB
			output SCLK2;				// Serial Clock, Pin 4, Port JB
output vga_h_sync, vga_v_sync, vga_R, vga_G, vga_B;
output St_ce_bar, St_rp_bar, Mt_ce_bar, Mt_St_oe_bar, Mt_St_we_bar;
output An0, An1, An2, An3, Ca, Cb, Cc, Cd, Ce, Cf, Cg, Dp;

	wire	reset, start, ClkPort, board_clk, clk, button_clk;
			wire SS;						// Active low
			wire MOSI;					// Data transfer from master to slave
			wire SCLK;					// Serial clock that controls communication
			wire SS2;						// Active low
			wire MOSI2;					// Data transfer from master to slave
			wire SCLK2;					// Serial clock that controls communication

			// Holds data to be sent to PmodJSTK
			wire [7:0] sndData;

			// Signal to send/receive data to/from PmodJSTK
			wire sndRec;

			// Data read from PmodJSTK
			wire [39:0] jstkData;
			wire [39:0] jstkData2;
			
			// Signal carrying output data that user selected
			wire [9:0] posData;
			wire [9:0] posData2;
			
			wire [15:0] bcdData;
			wire [15:0] bcdData2;
			
			// 1 kHz Clock Divider
			parameter cntEndVal = 16'hC350;
			reg [15:0] clkCount = 16'h0000;
			reg DCLK;
	
	BUF BUF1 (board_clk, ClkPort); 	
	BUF BUF2 (reset, BtnC);
	BUF BUF3 (start, Sw1);
	BUF BUF4 (Ack, Sw0);

	reg [27:0]	DIV_CLK;
	always @ (posedge board_clk, posedge reset)  
	begin : CLOCK_DIVIDER
      if (reset)
			DIV_CLK <= 0;
      else
			DIV_CLK <= DIV_CLK + 1'b1;
	end	

	assign	button_clk = DIV_CLK[18];
	assign	clk = DIV_CLK[1];
	assign 	{St_ce_bar, St_rp_bar, Mt_ce_bar, Mt_St_oe_bar, Mt_St_we_bar} = {5'b11111};

reg [1:0] state;
reg [2:0] p2_score;
reg [2:0] p1_score;
reg [5:0] checkBall;

wire inDisplayArea;
wire [9:0] CounterX;
wire [8:0] CounterY;

reg vga_R, vga_G, vga_B;

hvsync_generator syncgen(.clk(clk), .vga_h_sync(vga_h_sync), .vga_v_sync(vga_v_sync), 
  .inDisplayArea(inDisplayArea), .CounterX(CounterX), .CounterY(CounterY));
  
			PmodJSTK PmodJSTK_Int(
					.CLK(clk),
					.RST(reset),
					.sndRec(sndRec),
					.DIN(sndData),
					.MISO(MISO),
					.SS(SS),
					.SCLK(SCLK),
					.MOSI(MOSI),
					.DOUT(jstkData)
			);
			
			PmodJSTK PmodJSTK_Int2(
					.CLK(clk),
					.RST(reset),
					.sndRec(sndRec),
					.DIN(sndData),
					.MISO(MISO2),
					.SS(SS2),
					.SCLK(SCLK2),
					.MOSI(MOSI2),
					.DOUT(jstkData2)
			);
			
			Binary_To_BCD BtoBCD(
					.CLK(clk),
					.RST(reset),
					.START(DCLK),
					.BIN(posData),
					.BCDOUT(bcdData)
			);
			
			Binary_To_BCD BtoBCD2(
					.CLK(clk),
					.RST(reset),
					.START(DCLK),
					.BIN(posData2),
					.BCDOUT(bcdData2)
			);

			ClkDiv_5Hz genSndRec(
					.CLK(clk),
					.RST(reset),
					.CLKOUT(sndRec)
			);

localparam
 INI   = 2'b00,
 PLAY  = 2'b01,
 SCORE = 2'b10,
 DONE  = 2'b11,
 UNKN  = 2'bxx;
/////////////////////////////////////////////////////////////////
			always @(posedge clk) begin

							if(clkCount == cntEndVal) begin
									DCLK <= 1'b1;
									clkCount <= 16'h0000;
							end
							else begin
									DCLK <= 1'b0;
									clkCount <= clkCount + 1'b1;
							end
			end

/////////////////////////////////////////////////////////////////
assign posData = {jstkData[25:24], jstkData[39:32]};
assign posData2 = {jstkData2[25:24], jstkData2[39:32]};
assign sndData = {8'b10000000};

reg [8:0] PaddlePosition_L;
reg [8:0] PaddlePosition_R;

always @(posedge button_clk)
begin
	if(bcdData[11:8] > 4'b0101)
	begin
		if(~&PaddlePosition_R)        // make sure the value doesn't overflow
			PaddlePosition_R <= PaddlePosition_R + 1;
	end
	if(bcdData[11:8] < 4'b0101)
	begin
		if(|PaddlePosition_R)        // make sure the value doesn't underflow
			PaddlePosition_R <= PaddlePosition_R - 1;
	end
end

always @(posedge button_clk)
begin
	if(bcdData2[11:8] > 4'b0101)
	begin
		if(~&PaddlePosition_L)        // make sure the value doesn't overflow
			PaddlePosition_L <= PaddlePosition_L + 1;
	end
	if(bcdData2[11:8] < 4'b0101)
	begin
		if(|PaddlePosition_L)        // make sure the value doesn't underflow
			PaddlePosition_L <= PaddlePosition_L - 1;
	end
end

/////////////////////////////////////////////////////////////////
reg [9:0] ballX;
reg [8:0] ballY;
reg ball_inX, ball_inY;

always @(posedge clk)
if(ball_inX==0) ball_inX <= (CounterX==ballX) & ball_inY; else ball_inX <= !(CounterX==ballX+16);

always @(posedge clk)
if(ball_inY==0) ball_inY <= (CounterY==ballY); else ball_inY <= !(CounterY==ballY+16);

wire ball = ball_inX & ball_inY;

/////////////////////////////////////////////////////////////////
wire border = (CounterX[9:3]==0) || (CounterX[9:3]==79) || (CounterY[8:3]==0) || (CounterY[8:3]==59);
wire paddle_R = (CounterX>=PaddlePosition_R+8) && (CounterX<=PaddlePosition_R+120) && (CounterY[8:4]==27);
wire paddle_L = (CounterX>=PaddlePosition_L+8) && (CounterX<=PaddlePosition_L+120) && (CounterY[8:4]==2);
wire BouncingObject = border | paddle_L | paddle_R; // active if the border or paddle is redrawing itself

reg ResetCollision;
always @(posedge clk) ResetCollision <= (CounterY==500) & (CounterX==0);  // active only once for every video frame

reg CollisionX1, CollisionX2, CollisionY1, CollisionY2;
always @(posedge clk) if(ResetCollision) CollisionX1<=0; else if(BouncingObject & (CounterX==ballX   ) & (CounterY==ballY+ 8)) CollisionX1<=1;
always @(posedge clk) if(ResetCollision) CollisionX2<=0; else if(BouncingObject & (CounterX==ballX+16) & (CounterY==ballY+ 8)) CollisionX2<=1;
always @(posedge clk) if(ResetCollision) CollisionY1<=0; else if(BouncingObject & (CounterX==ballX+ 8) & (CounterY==ballY   )) CollisionY1<=1;
always @(posedge clk) if(ResetCollision) CollisionY2<=0; else if(BouncingObject & (CounterX==ballX+ 8) & (CounterY==ballY+16)) CollisionY2<=1;

/////////////////////////////////////////////////////////////////
wire UpdateBallPosition = ResetCollision;  // update the ball position at the same time that we reset the collision detectors

reg ball_dirX, ball_dirY;
always @(posedge clk)
if(UpdateBallPosition)
begin
	if(~(CollisionX1 & CollisionX2))        // if collision on both X-sides, don't move in the X direction
	begin
		ballX <= ballX + (ball_dirX ? -1 : 1);
		if(CollisionX2) ball_dirX <= 1; else if(CollisionX1) ball_dirX <= 0;
	end

	if(~(CollisionY1 & CollisionY2))        // if collision on both Y-sides, don't move in the Y direction
	begin
		ballY <= ballY + (ball_dirY ? -1 : 1);
		if(CollisionY2) ball_dirY <= 1; else if(CollisionY1) ball_dirY <= 0;
	end
		
	if (state == SCORE)
	begin
		ballY <= 180;
	end
	
end 

/////////////////////////////////////////////////////////////////
wire R = BouncingObject | ball | (CounterX[3] ^ CounterY[3]);
wire G = BouncingObject | ball;
wire B = BouncingObject | ball;

always @(posedge clk)
begin
	vga_R <= R & inDisplayArea;
	vga_G <= G & inDisplayArea;
	vga_B <= B & inDisplayArea;
end
/////////////////////////////////////////////////////////////////
//////////////  	  State Machine 	 ////////////////////////////
/////////////////////////////////////////////////////////////////
always @(DIV_CLK[21])
begin
	checkBall <= ballY[8:4];

end


//start of state machine
always @(posedge DIV_CLK[21], posedge reset) //asynchronous active_high Reset
 begin  
	   if (reset) 
	       begin
				p2_score <= 3'bXXX;
				p1_score <= 3'bXXX;
			   state <= INI;
	       end
       else // under positive edge of the clock
         begin
            case (state) // state and data transfers
                 INI:
						begin
						// state transitions
							if(start) 
								state <= PLAY;
						// RTL
							p2_score <= 3'b000;
							p1_score <= 3'b000;
					   end      
                 PLAY:     
                    begin  
					// state transitions
							if ((checkBall <= 1) || (checkBall >= 27))
								state <= SCORE;				
					//RTL
							
							if (checkBall <= 1)
								p1_score <= p1_score + 1;
							if (checkBall >= 27)
								p2_score <= p2_score + 1;
						  end
                 SCORE:      
							begin   
							// state transitions
								if ((p1_score == 5) || (p2_score == 5))
									state <= DONE;
								else 
									state <= PLAY;
							//RTL
								
                    end 
                 DONE:
                    begin
							if(Ack)
								state <= INI;
                    end
				default: 
                    begin
                         state <= UNKN;    
                    end
            endcase
         end   
 end // end of always procedural block 



/////////////////////////////////////////////////////////////////
//////////////  	  State Machine End 	 /////////////////////////
/////////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////
	//////////////  	  SSD control starts here 	 ///////////////////
	/////////////////////////////////////////////////////////////////
	reg 	[3:0]	SSD;
	wire 	[3:0]	SSD0, SSD1, SSD2, SSD3;
	wire 	[1:0] ssdscan_clk;
	
	assign SSD3 = p2_score[2:0];
	assign SSD2 = 4'b1111;
	assign SSD1 = 4'b1111;
	assign SSD0 = p1_score[2:0];
	
	// need a scan clk for the seven segment display 
	// 191Hz (50MHz / 2^18) works well
	assign ssdscan_clk = DIV_CLK[19:18];	
	assign An0	= !(~(ssdscan_clk[1]) && ~(ssdscan_clk[0]));  // when ssdscan_clk = 00
	assign An1	= !(~(ssdscan_clk[1]) &&  (ssdscan_clk[0]));  // when ssdscan_clk = 01
	assign An2	= !( (ssdscan_clk[1]) && ~(ssdscan_clk[0]));  // when ssdscan_clk = 10
	assign An3	= !( (ssdscan_clk[1]) &&  (ssdscan_clk[0]));  // when ssdscan_clk = 11
	
	always @ (ssdscan_clk, SSD0, SSD1, SSD2, SSD3)
	begin : SSD_SCAN_OUT
		case (ssdscan_clk) 
			2'b00:
					SSD = SSD0;
			2'b01:
					SSD = SSD1;
			2'b10:
					SSD = SSD2;
			2'b11:
					SSD = SSD3;
		endcase 
	end	

	// and finally convert SSD_num to ssd
	reg [6:0]  SSD_CATHODES;
	assign {Ca, Cb, Cc, Cd, Ce, Cf, Cg, Dp} = {SSD_CATHODES, 1'b1};
	// Following is Hex-to-SSD conversion
	always @ (SSD) 
	begin : HEX_TO_SSD
		case (SSD)		
			4'b1111: SSD_CATHODES = 7'b1111111 ; //Nothing 
			4'b0000: SSD_CATHODES = 7'b0000001 ; //0
			4'b0001: SSD_CATHODES = 7'b1001111 ; //1
			4'b0010: SSD_CATHODES = 7'b0010010 ; //2
			4'b0011: SSD_CATHODES = 7'b0000110 ; //3
			4'b0100: SSD_CATHODES = 7'b1001100 ; //4
			4'b0101: SSD_CATHODES = 7'b0100100 ; //5
			4'b0110: SSD_CATHODES = 7'b0100000 ; //6
			4'b0111: SSD_CATHODES = 7'b0001111 ; //7
			4'b1000: SSD_CATHODES = 7'b0000000 ; //8
			4'b1001: SSD_CATHODES = 7'b0000100 ; //9
			4'b1010: SSD_CATHODES = 7'b0001000 ; //10 or A
			default: SSD_CATHODES = 7'bXXXXXXX ; // default is not needed as we covered all cases
		endcase
	end
	
	/////////////////////////////////////////////////////////////////
	//////////////  	  SSD control ends here 	 ///////////////////
	/////////////////////////////////////////////////////////////////
endmodule 