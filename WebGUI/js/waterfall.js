// Creates a WaterFall plot

var WaterFall = function(myCanvas)
{
    this.c = myCanvas;
    this.ctx = this.c.getContext('2d');
    this.h_step = this.c.width / 64;
    this.v_step = this.h_step * 3/4;
    this.h_size = this.h_step;
    this.v_size = this.v_step;
};

WaterFall.prototype.UpdateMargins = function(h_margin, v_margin)
{
    this.h_size = this.h_step - h_margin;
    this.v_size = this.v_step - v_margin;
    this.ctx.clearRect(0, 0, this.c.width, this.c.height);
};

WaterFall.prototype.Update = function(data)
{
    // "Roll" the canvas by copying the previous drawing
    this.ctx.drawImage(this.c, 0, this.v_step);
    // Unless we change the spacing, the following is not needed
    //this.ctx.clearRect(0, 0, this.c.width, this.v_step);
    // Draw the new row of data
    for (var p = 0; p < 64; p++) {
        var tp = (data[p] << 2) - (data[p] >> 2); // == 15*data[i]/4 == 360*data[i]/64
        this.ctx.fillStyle = "hsl(" + tp + ",100%,50%)";
        this.ctx.fillRect(p * this.h_step, 0, this.h_size, this.v_size);
    }    
};
