# coding: utf-8
require "pp"

if (RUBY_PLATFORM.downcase=~/mswin(?!ce)|mingw|cygwin|bccwin/)
  #Windows
  require "c:\\windowscomport.rb"
  pp "Windows"
else
  require "./linuxcomport.rb"
 pp "Linux"
end

#構造体定義
FontData=Struct.new("FontData",:char,:dot_data)
fontdatas = Array.new
mode = nil
bitmap=[]
char=nil
File.foreach("./font_src.bit", :encoding => Encoding::EUC_JP){ |f|
  if /BITMAP/ =~f
    bitmap=[]
    char=nil
    mode="BMP"
  elsif mode=="BMP" && /ENDCHAR/ =~f
    mode="START"
    char= f.delete("ENDCHAR #").encode("UTF-8","EUC-JP").chop
    fontdatas << FontData.new(char,bitmap)
  elsif mode=="BMP"
    bitmap.push f.chop.gsub(".","0").gsub("@","1").to_i(2)
  end
}

sendData=[]
string="やっと出来ました！ヒムヒムまじひむ★。ながーーい文章。漢字もＯＫ。今の所全角文字だけ。フロー制御とダブルバッファを実装！これで散髪に行ける。広島電子工作娯楽部（仮）Ｈｉｒｏｓｈｉｍａ．ｒｂ広島鯖ユーザ友の会（仮称）ＯＳＣ２０１３広島開催！　　"
string.split(//).each{|c|
  fontdatas.each{|d|
    if(d.char.to_s==c)
  puts c

     sendData.push d.dot_data
    end
  }
}
sendData.flatten!
#pp sendData



com = Com.new
com.open
12.times do
    com.put_bin(sendData)
#   sleep(0.5)
  end
com.close



puts "Start"
