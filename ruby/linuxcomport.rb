# coding: utf-8
#タイミングの問題か、Linuxでは上手く動作しない。
class Com
  def open(defport="/dev/ttyACM0")
    @com = File.open(defport,"r+b")
    system(" stty<#{defport}  57600")  
  end

  def close
    @com.close
  end
    def put_bit(b)
    chk=0
    tmp=Array.new
      puts "0x#{b.to_s(16)}"
    @com.putc(b)
    @com.flush
#    sleep(0.05)
    while(chk) do
pp "start"
sleep(1)
      tmp=@com.sysread(1)
pp "Get"
      pp tmp
      tmp=tmp.unpack("C")
      pp tmp[0]
      if (tmp[0]==b)
        pp "OK"
        break
      end
      pp "chking..."
#      sleep(0.05)
#      @com.putc(b)
    end
  end

  def get_bin
    #x.times do
    # c = @com.sysread(1)
    #pp @com.methods
    1.times do
      pp @com.sysread(4)
    end
    #@com.flush
    #end
  end
  def put_bin(x)
    x.each{|d|
      #16bitのデータを上位8bit、下位8bitに分けて送信
      high_bit=d >> 8
      low_bit=d & 255
#      puts "0x#{high_bit.to_s(16)}"
#      puts "0x#{low_bit.to_s(16)}"
#      @com.putc(high_bit)  #上位ビット
#      @com.putc(low_bit)   #下位ビット
       put_bit(high_bit)
       put_bit(low_bit)
#      sleep(0.05)
    }
    puts "Send"
  end
end