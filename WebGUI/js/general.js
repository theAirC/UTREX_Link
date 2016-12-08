// General functions

function g(id) { return document.getElementById(id); }

function arraySwap(array, index0, index1) {
    var c = array[index0];
    array[index0] = array[index1];
    array[index1] = c;
}

function domSwap(parentNode, index0, index1) {
    if (index0 > index1) { var c = index0; index0 = index1; index1 = c; }
    var node0 = parentNode.childNodes[index0];
    var node1 = parentNode.childNodes[index1];
    var node1plus = parentNode.childNodes[index1].nextSibling;
    // move node1 to just above node0
    parentNode.insertBefore(node1, node0);
    // move node0 to just above node1plus, i.e. to exactly where node1 was
    parentNode.insertBefore(node0, node1plus);
}

// Returns the val that corresponds to the key that matches the input,
// or the input as is, if no key matches.
function match2(input, key0, key1, val0, val1) {
    if (input == key0) return val0;
    else if (input == key1) return val1;
    else return input;
}
