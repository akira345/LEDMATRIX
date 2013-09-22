class Com
  attr_accessor :comno, :speed, :parity , :data , :stop
  def initialize
    @comno="3"
    @speed="9600"
    @parity="N"
    @data="8"
    @stop="1"
  end

  def comOpen(n)
    @comno=n.to_s
    modestr = "MODE COM#{@comno} BAUD=#{@speed} PARITY=#{@parity} DATA=#{@data} STOP=#{@stop}"
    system modestr
    @com = open("com#{@comno}", "r+b")#.binmode
  end

  def comClose
    @com.close
  end

  def putbin(x)
    x.each{|d|
#16bit�̃f�[�^�����8bit�A����8bit�ɕ����đ��M
      @com.putc(d >> 8)  #��ʃr�b�g
      @com.putc(d & 255) #���ʃr�b�g
#sleep(1)
    }
    puts "Send"
  end

  def readDump(n)
    d = 0
    for i in 1..n
      c = @com.sysread(1)
      d = c[0]
      printf("%02X ",d)
    end
    puts
  end

end

sendData=[
#0x0020,0x607e,0x3184,0x1648,0x0130,0x00c0,0x0700,0xf1fc, 0x1320,0x1020,0x17ff,0x1020,0x1222,0x33fe,0x6800,0xc7ff,
0x0000,0x00f8,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020, 0x0020,0x0020,0x0020,0x1020,0x1840,0x0f80,0x0000,0x0000 ,
#0x0020,0x607e,0x3184,0x1648,0x0130,0x00c0,0x0700,0xf1fc, 0x1320,0x1020,0x17ff,0x1020,0x1222,0x33fe,0x6800,0xc7ff,
#0x0000,0x00f8,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020, 0x0020,0x0020,0x0020,0x1020,0x1840,0x0f80,0x0000,0x0000 ,
#0x0000,0x00f8,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020, 0x0020,0x0020,0x0020,0x1020,0x1840,0x0f80,0x0000,0x0000 ,

]
#sendData=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
com1=Com.new
com1.comOpen(3)
3.times do
com1.putbin(sendData)
#sleep(1)
end
#com1.readDump(22)

com1.comClose