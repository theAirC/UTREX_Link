
var log_div = g("bottom");
var log_p = g("bottom").childNodes[5];

function log(level, msg) {

    log_p.textContent = msg;
}

function clearLog() {
    log();
}
