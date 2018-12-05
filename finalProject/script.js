console.log("Hello World");

var calcString = [];
var answer = 0;

$(document).ready(function(){
    $("#screen").val(answer);
    // append values from button press to array
    $("input").click(function() {
        var value = $(this).val();
        // numerical checks for appending value to array
        if ($.isNumeric(value)) {
            calcString.push(value);
        }
        // operator checks for appending value to array
        if ( ["+", "-", "*", "/", ".", "^"].includes(value)) {
            if (calcString.length != 0) {
                if (!["+", "-", "*", "/", ".", "^"].includes(calcString[calcString.length - 1])) {
                    calcString.push(value);
                    // console.log(calcString[-1]);
                }
            }
        }
        // implement parenthesis
        if (["(", ")"].includes(value)) {
            calcString.push(value);
        }
        // implement calc cancelling buttons
        if (value == "DEL" || value == "AC") {
            calcString = [];
        }
        
        // update calculator screen
        if (value != "=") {
            $("#screen").val(calcString.join(""));
            console.log(calcString.join(""));
        }
        else {
            answer = eval(calcString.join(""));
            $("#screen").val(answer);
            console.log(answer);
            calcString = [];
        }
        
    })

    // cancel out post button click focus
    $("btn").mouseup(function(){
        $(this).blur();
    })
})
