# coding: utf-8
class Com
  def open(defport="/dev/ttyACM0")
    @com = File.open(defport,"r+b")
    system(" stty<#{defport}  9600")  
  end

  def close
    @com.close
  end

  def put_bin(x)
    x.each{|d|
      #16bitのデータを上位8bit、下位8bitに分けて送信
      high_bit=d >> 8
      low_bit=d & 255
      puts "0x#{high_bit.to_s(16)}"
      puts "0x#{low_bit.to_s(16)}"
      @com.putc(high_bit)  #上位ビット
      @com.putc(low_bit)   #下位ビット
      @com.flush
      sleep(0.08)
    }
    puts "Send"
 end
end