# Saves curve data in (u16) raw file to be used by UTREX_Link
# example use : MakeCurve(@(x) x^2);
# Make sure the given function (x^2 in the example)
# is within [0..1] when x is within [0..1]

function MakeCurve(func, filename)
  x = 0.5:1:65535.5;
  y = round(func(x/65536)*65536);
  
  plot(x, y);
  margin = 4096;
  axis([-margin, 65535 + margin, -margin, 65535 + margin]);
  set(gca,'XTick',0:8192:65536);
  set(gca,'YTick',0:8192:65536);
  grid on;
  
  myfile = fopen(filename, "w");
  fwrite(myfile, y, "uint16", 0, "l");
  fclose(myfile);
endfunction
