console.log("Hello World");

var calcString = [];

$(document).ready(function(){
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
        // get answer
        if (value == "=") {
            answer = eval(calcString.join(""));
            console.log(answer);
            calcString = [];
        }
        
        console.log(calcString);
    })

    // cancel out post button click focus
    $("btn").mouseup(function(){
        $(this).blur();
    })
})
