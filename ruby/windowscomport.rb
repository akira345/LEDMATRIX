# coding: utf-8
class Com
  def open(defport="3")
    modestr = "MODE COM#{@defport} BAUD=9600 PARITY=N DATA=8 STOP=1"
    system modestr
    @com = open("com#{@defport}", "r+b")#.binmode
  end

  def close
    @com.close
  end

  def putbin(x)
    x.each{|d|
      #16bitのデータを上位8bit、下位8bitに分けて送信
      high_bit=d >> 8
      low_bit=d & 255
#      puts "0x#{high.to_s(16)}"
#      puts "0x#{low.to_s(16)}"
      @com.putc(high)  #上位ビット
      @com.putc(low)   #下位ビット
      @com.flush
      sleep(0.05)
    }
    puts "Send"
  end
end