module mdio_ctrl(
	input				clk				,
	input				rst_n			,
	input				soft_rst_trig	,
	input				op_done			,	
	input		[15:0]	op_rd_data		,
	input				op_rd_ack		,
	output	reg			op_exec			,
	output	reg			op_rh_wl		,
	output	reg	[4:0]	op_addr			,		
	output	reg	[15:0]	op_wr_data		,		
	output		[1:0]	led
	);

	
reg				rst_trig_d0;	
reg				rst_trig_d1;
reg				rst_trig_flag;
reg		[23:0]	timer_cnt;		
reg				timer_done;
reg				start_next;
reg				read_next;
reg				link_error;
reg		[2:0]	flow_cnt;	
reg		[1:0]	speed_status;

wire			pos_rst_trig;
//采soft_rst_trig信号上升沿
assign	pos_rst_trig = ~rst_trig_d1 & rst_trig_d0;
//未连接或连接失败时led赋值00
//01:10Mbps	10:100Mbps 11:1000Mbps 00:其他情况
assign	led = link_error ? 2'b00: speed_status;
//对soft_rst_trig信号延时打拍
always	@(posedge clk or negedge rst_n) begin
	if(!rst_n) begin
		rst_trig_d0 <= 1'b0;
		rst_trig_d1 <= 1'b0;
	end
	else begin
		rst_trig_d0 <= soft_rst_trig;
		rst_trig_d1 <= rst_trig_d0;
	end
end
//定时计数
always @(posedge clk or negedge rst_n) begin
	if(!rst_n) begin
		timer_cnt <= 1'b0;
		timer_done <= 1'b0;
	end
	else begin
		if(timer_cnt == 24'd1_000_000 - 1'b1) begin
			timer_done <= 1'b0;
			timer_cnt <= timer_cnt + 1'b1;
		end
		else begin
			timer_done <= 1'b0;
			timer_cnt <= timer_cnt + 1'b1;
		end
	end
end

//根据软复位信号对MDIO接口进行软复位，并定时读取以太网的连接状态
always @(posedge clk or negedge rst_n) begin
	if(!rst_n) begin
		flow_cnt <= 3'd0;
		rst_trig_flag <= 1'b0;
		speed_status <= 2'b00;
		op_exec <= 1'b0;
		op_rh_wl <= 1'b0;
		op_addr <= 1'b0;
		op_wr_data <= 1'b0;
		start_next <= 1'b0;
		read_next <= 1'b0;
		link_error <= 1'b0;
	end
	else begin
		op_exec <= 1'b0;
		if(pos_rst_trig)
			rst_trig_flag <= 1'b1;
		case(flow_cnt)
			2'd0: begin
				if(rst_trig_flag) begin
					op_exec <= 1'b1;
					op_rh_wl <= 1'b0;
					op_addr <= 5'h00;
					op_wr_data <= 16'h9140;
					flow_cnt <= 3'd1;
				end
				else if(timer_done) begin
					op_exec <= 1'b1;
					op_rh_wl <= 1'b1;
					op_addr <= 5'h01;
					flow_cnt <= 3'd2;
				end
				else if(start_next) begin
					op_exec <= 1'b1;
					op_rh_wl <= 1'b1;
					op_addr <= 5'h11;
					flow_cnt <= 3'd2;
					start_next <= 1'b0;
					read_next <= 1'b1;
				end
			end
			2'd1 : begin
				if(op_done) begin
					flow_cnt <= 3'd0;
					rst_trig_flag <= 1'b0;
				end
			end
			2'd2 : begin
				if(op_done) begin //MDIO接口读操作完成
					if(op_rd_ack == 1'b0 && read_next == 1'b0)
						flow_cnt <= 3'd3;
					else if(op_rd_ack == 1'b0 && read_next == 1'b1)begin
						read_next <= 1'b0;
						flow_cnt <= 3'd4;
					end
					else begin
						flow_cnt <= 3'd0;
					end
				end
			end
			2'd3 : begin
				flow_cnt <= 3'd0; //链路正常并且自协商完成
				if(op_rd_data[5] == 1'b1 && op_rd_data[2] == 1'b1) begin
					start_next <= 1;
					link_error <= 0;
				end
				else begin
					link_error <= 1'b1;
				end
			end
			3'd4 : begin
				flow_cnt <= 3'd0;
				if(op_rd_data[15:14] == 2'b10)
					speed_status <= 2'b11;
				else if(op_rd_data[15:14] == 2'b01)
					speed_status <= 2'b10;
				else if(op_rd_data[15:14] == 2'b00)
					speed_status <= 2'b01;
				else
					speed_status <= 2'b00;
			end
		endcase
	end
end
endmodule