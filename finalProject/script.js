console.log("Hello World");

$(document).ready(function(){
    // get digit
    // var value = document.getElementById("digit").onclick = function() {
    //     return this.value;
    // }
    // function getValue() {
    //     var digit = document.getElementById("digit").value;
    //     console.log(this.value);
    // }
    // $("#digit").click(getValue);
    $("input").click(function() {
        var value = $(this).val();
        console.log(value);
    })

    // cancel out post button click focus
    $("btn").mouseup(function(){
        $(this).blur();
    })
})
