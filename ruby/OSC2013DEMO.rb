# coding: utf-8
require "pp"
require "twitter"
require "moji"

Twitter.configure do |config|
  config.consumer_key = "<コンシューマーキー>"
  config.consumer_secret = "<シークレットキー>"
end
client = Twitter::Client.new(
  :oauth_token => "<トークン>",
  :oauth_token_secret => "<トークンシークレット>"
)

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
string = ""
client.search("osc13hi", lang: "ja", count: 300).results.map do |status| #ハッシュタグ指定
#  p  "#{status.text}"
string  =  string  +  "　　　"  +  Moji.han_to_zen(("@" + status.from_user + "：" + status.text).encode('utf-8'))
end
#string="あいうえお漢字"
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



