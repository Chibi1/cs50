console.log("Hello World");

$(document).ready(function(){
    // get digit
    // var value = document.getElementById("digit").onclick = function() {
    //     return this.value;
    // }
    function getValue(val) {
        alert(val.value);
        
    }

    // cancel out post button click focus
    $("btn").mouseup(function(){
        $(this).blur();
    })
})
