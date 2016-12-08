var main_div = g("main");
var canvas = g("c");
var ctx = canvas.getContext("2d");

var j = JSON.parse(localStorage.getItem('UTREX_Config'));

var isDown = false;
var prevPad;
var prevPadColumn = 0;
var prevGroupID = 0;
var prevControlID = 0;
var maps = [j.MapMixer, j.MapOutput];

function deleteLine() {
    if (isDown) {
        if (prevPadColumn % 2 != 0) {
            clearPadBG(prevPadColumn, prevGroupID, prevControlID);
            var tp = maps[(prevPadColumn-1)/2][prevGroupID][prevControlID];
            if (tp[0] >= 0) clearPadBG(prevPadColumn-1, tp[0], tp[1]);
            tp[0] = -1;
            tp[1] = -1;
        }
        endLine();
    }
}

function endLine() {
    isDown = false;
    prevPad.style.background = "";
    fixCanvas();
}

function ControlBarClicked(pad, padColumn, groupID, controlID) {
    if (isDown == true) {
        // Output pads are at even columns, input pads are at odd columns.
        if (padColumn % 2 == 0) {
            // Swap current and previous
            var t = padColumn; padColumn = prevPadColumn; prevPadColumn = t;
            var t = groupID;   groupID   = prevGroupID;   prevGroupID   = t;
            var t = controlID; controlID = prevControlID; prevControlID = t;
        }

        // Matching pads have succesive column (i.e. the first output pads have column = 0,
        //                                           so they connect only to input pads of column = 1)
        if ((padColumn - prevPadColumn == 1) && ((padColumn != 1) || (j.MixerInputs[groupID][controlID] == j.InputControls[prevGroupID][prevControlID]))) {
            var tp = maps[prevPadColumn/2][groupID][controlID];
            if (tp[0] >= 0) clearPadBG(prevPadColumn, tp[0], tp[1]);
            tp[0] = prevGroupID;
            tp[1] = prevControlID;

            clearLog();
        }
        else log(2, "Can't connect these controls");
        endLine();
    }
    else {
        isDown = true;
        prevPad = pad;
        prevPadColumn = padColumn;
        prevGroupID = groupID;
        prevControlID = controlID;

        var coord = pad.getBoundingClientRect();
        var y = (coord.top + coord.bottom) / 2 + window.pageYOffset;
        var x = (coord.left + coord.right) / 2 + window.pageXOffset;
        ctx.beginPath();
        ctx.moveTo(x, y);
        ctx.strokeStyle = Colors.activeLine;
        pad.style.background = Colors.activePadBG;
    }
}

function fixCanvas() {
    canvas.height = main_div.clientHeight;
    canvas.width = main_div.clientWidth;
    ctx.strokeStyle = Colors.connectLine;
    ctx.lineWidth = 4;

    for (var mapID = 0; mapID < maps.length; mapID++) {
        for (var groupID = 0; groupID < maps[mapID].length; groupID++) {
            for (var controlID = 0; controlID < maps[mapID][groupID].length; controlID++) {
                var otherPadID = maps[mapID][groupID][controlID];

                if (otherPadID[0] >= 0) {
                    var pad = getCoords(setPadBG(mapID*2 + 1, groupID, controlID));
                    ctx.moveTo(pad.x, pad.y);
                    pad = getCoords(setPadBG(mapID*2, otherPadID[0], otherPadID[1]));
                    ctx.lineTo(pad.x, pad.y);
                }
            }
        }
    }

    ctx.stroke();
}

function save() {
    try {
        localStorage.setItem('UTREX_Config', JSON.stringify(j));
        log(0, "Saved")
    }
    catch(error) {
        log(4, "Failed to save !! reason: " + error.message);
    }
}

function refresh() {
    location.reload();
}

function swapGroups(column, groupID0, groupID1) {
    switch (column) {
        case 0:
            // Input groups
            arraySwap(j.InputNames, groupID0, groupID1);
            arraySwap(j.InputGUIDs, groupID0, groupID1);
            arraySwap(j.InputControls, groupID0, groupID1);
            // Find the j.MapMixer[x][y][0] == groupID0 or groupID1 and replace with the other.
            for (var x = 0; x < j.MapMixer.length; x++) {
                for (var y = 0; y < j.MapMixer[x].length; y++) {
                    j.MapMixer[x][y][0] = match2(j.MapMixer[x][y][0], groupID0, groupID1, groupID1, groupID0);
                }
            }
            break;
        case 1:
            // Mixer groups
            arraySwap(j.MixerNames, groupID0, groupID1);
            arraySwap(j.MixerInputs, groupID0, groupID1);
            arraySwap(j.MapMixer, groupID0, groupID1);
            // Find the j.MapOutput[x][y][0] == groupID0 or groupID1 and replace with the other.
            for (var x = 0; x < j.MapOutput.length; x++) {
                for (var y = 0; y < j.MapOutput[x].length; y++) {
                    j.MapOutput[x][y][0] = match2(j.MapOutput[x][y][0], groupID0, groupID1, groupID1, groupID0);
                }
            }
            break;
        case 2:
            // Output groups
            arraySwap(j.OutputNames, groupID0, groupID1);
            arraySwap(j.OutputRIDs, groupID0, groupID1);
            arraySwap(j.OutputChannels, groupID0, groupID1);
            arraySwap(j.OutputCurves, groupID0, groupID1);
            arraySwap(j.MapOutput, groupID0, groupID1);
    }
    save();
    refresh();
}

main_div.addEventListener("mousemove", function(ev) {
    if (!isDown) return;
    var x = ev.clientX;
    var y = ev.clientY;
    ctx.lineTo(x, y);
    ctx.stroke();
});

var top_bar = g("top");
top_bar.childNodes[0].addEventListener("click", endLine);
top_bar.childNodes[1].addEventListener("click", deleteLine);
top_bar.childNodes[2].addEventListener("click", save);

window.addEventListener("keyup", function(ev) {
    switch(ev.key) {
        case "Escape": endLine(); break;
        case "d": deleteLine(); break;
        case "s": save(); break;
    }
});

window.addEventListener("resize", fixCanvas);
