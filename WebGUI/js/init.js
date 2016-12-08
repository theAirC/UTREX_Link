// Initialization - runs only once when loaded.

for (var i = 0; i < j.InputControls.length; i++) {
    guiMap[0][i] = [];
    var c = makeControlGroup(j.InputNames[i], 0, i);
    for (var b = 0; b < j.InputControls[i].length; b++) {
        var txt = ControlTypeNames[j.InputControls[i][b]];
        c.appendChild(makeControlBar(txt, 0, i, b));
    }

    g("InputDevices").appendChild(c);
}

for (var i = 0; i < j.MixerNames.length; i++) {
    guiMap[1][i] = [];
    guiMap[2][i] = [];
    var c = makeControlGroup(j.MixerNames[i], 1, i);
    c.childNodes[1].appendChild(makeControlPad(2, i, 0));
    for (var b = 0; b < j.MixerInputs[i].length; b++) {
        var txt = ControlTypeNames[j.MixerInputs[i][b]];
        c.appendChild(makeControlBar(txt, 1, i, b));
    }

    g("Mixers").appendChild(c);
}

for (var i = 0; i < j.OutputChannels.length; i++) {
    guiMap[3][i] = [];
    var c = makeControlGroup(j.OutputNames[i], 2, i);
    for (var b = 0; b < j.OutputChannels[i].length; b++) c.appendChild(makeControlBar(j.OutputChannels[i][b] + " : " + j.OutputCurves[i][b], 3, i, b));

    g("OutputDevices").appendChild(c);
}

fixCanvas();
