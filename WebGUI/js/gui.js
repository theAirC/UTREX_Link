// GUI related functions

// The following map relates pad IDs to pads (DOM references).
var guiMap = [[],[],[],[]];
var ControlTypeNames = ["Delta", "Range", "State", "Button"];

var toolFunctions = [
    function(column, groupID) {if (groupID > 0) swapGroups(column, groupID-1, groupID);},
    function(column, groupID) {swapGroups(column, groupID, groupID+1);}
];

var Colors = {
    downBG: "#bfbfbf",
    connectPadBG: "#00df00",
    connectLine: "#00df00",
    activePadBG: "#dfdf00",
    activeLine: "#dfdf00",
};

function getCoords(pad) {
    var coord = pad.getBoundingClientRect();
    var x = (coord.left + coord.right) / 2 + window.pageXOffset;
    var y = (coord.top + coord.bottom) / 2 + window.pageYOffset;
    return {x: x, y: y};
}

function clearPadBG(padColumn, groupID, controlID) {
    var pad = guiMap[padColumn][groupID][controlID];
    pad.style.background = "";
    return pad;
}

function setPadBG(padColumn, groupID, controlID) {
    var pad = guiMap[padColumn][groupID][controlID];
    pad.style.background = Colors.connectPadBG;
    return pad;
}

function ControlTools_Show(groupNode) {
    groupNode.childNodes[0].style.visibility = "";
    groupNode.childNodes[1].childNodes[0].style.display = "none";
    groupNode.childNodes[1].childNodes[1].style.display = "";
}

function ControlTools_Hide(groupNode) {
    groupNode.childNodes[0].style.visibility = "hidden";
    groupNode.childNodes[1].childNodes[0].style.display = "";
    groupNode.childNodes[1].childNodes[1].style.display = "none";
}

function pText(text) { var t = document.createElement("p"); t.appendChild(document.createTextNode(text)); return t; }

function makeControlPad(padColumn, groupID, controlID) {
    var pad = document.createElement("div");
    pad.className = "ControlPad";
    pad.addEventListener("click", function() { ControlBarClicked(pad, padColumn, groupID, controlID); });
    guiMap[padColumn][groupID][controlID] = pad;
    return pad;
}

// ControlBars are the range/delta/state/button/channel bars.
function makeControlBar(Name, padColumn, groupID, controlID) {
    var e = document.createElement("div");
    e.className = "ControlBar";
    
    e.appendChild(pText(Name));
    e.appendChild(makeControlPad(padColumn, groupID, controlID));

    return e;
};

function makeControlTool(toolType, column, groupID) {
    var s = document.createElement("img");
    s.src = "img/tool" + toolType + ".svg";
    s.addEventListener("click", function() { toolFunctions[toolType](column, groupID); });
    return s;
}

function makeControlGroup(Name, column, groupID) {
    // Create the ControlGroup
    var e = document.createElement("div");
    e.className = "ControlGroup";
    
    // Create the ControlTools
    var ee = document.createElement("div");
    ee.className = "ControlTools";
    ee.style.visibility = "hidden";
    for (var i = 0; i < 8; i++) ee.appendChild(makeControlTool(i, column, groupID));
    e.appendChild(ee);

    // Create the ControlHeader
    ee = document.createElement("div");
    ee.className = "ControlHeader";
    var s = document.createElement("img");
    s.src = "img/up.svg";
    s.addEventListener("click", function() { ControlTools_Show(e); });
    ee.appendChild(s);
    s = document.createElement("img");
    s.src = "img/down.svg";
    s.style.background = Colors.downBG;
    s.addEventListener("click", function() { ControlTools_Hide(e); });
    s.style.display = "none";
    ee.appendChild(s);
    ee.appendChild(pText(Name));
    e.appendChild(ee);

    return e;
}
