# coding: utf-8
class Com
  def open(defport="3")
    modestr = "MODE COM#{defport} BAUD=57600 PARITY=N DATA=8 STOP=1"
    system modestr
    @com = File.open("com#{defport}", "r+b")#.binmode
  end

  def close
    @com.close
  end
  def put_bit(b)
    chk=0
    tmp=Array.new
    puts "0x#{b.to_s(16)}"
#1byte送信
    @com.putc(b)
    @com.flush
#    sleep(0.05)
    while(chk) do
pp "start"
#1byte受信
      tmp=@com.sysread(1)
pp "Get"
      pp tmp
      tmp=tmp.unpack("C")
      pp tmp[0]
#送信したデータと受信したデータが一致するか？
#一致しなければ待つ
      if (tmp[0]==b)
        pp "OK"
        break
      end
      pp "chking..."
#      sleep(0.05)
#      @com.putc(b)
    end
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