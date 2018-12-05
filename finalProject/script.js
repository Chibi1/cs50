// console.log("Hello World");

var calcString = ["0"];
var answer = "0";
answered = true;

$(document).ready(function(){
    $("#screen").val(answer);
    // append values from button press to array
    $("input").click(function() {
        var value = $(this).val();
        // numerical checks for appending value to array
        if ($.isNumeric(value)) {
            // check whether new calc should start or can append num to previous calculation
            if (answered == true) {
                answered = false;
                calcString = [];
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            else {
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            
        }
        // operator checks for appending value to array
        if ( ["+", "-", "*", "/", ".", "^"].includes(value)) {
            answered = false;
            if (calcString.length != 0) {
                if (!["+", "-", "*", "/", ".", "^"].includes(calcString[calcString.length - 1])) {
                    calcString.push(value);
                    $("#screen").val(calcString.join(""));
                    // console.log(calcString[-1]);
                }
            }
        }
        // implement parenthesis
        if (["(", ")"].includes(value)) {
            calcString.push(value);
            $("#screen").val(calcString.join(""));
        }
        // implement delete button
        if (value == "DEL") {
            answer = 0;
            $("#screen").val(answer);
            console.log(answer);
            calcString = [];
        }
        
        // update calculator screen
        if (value != "=") {
            
            // console.log(calcString.join(""));
        }
        else {
            if (calcString.length != 0) {
                answer = eval(calcString.join(""));
                $("#screen").val(answer);
                answered = true;
                console.log(answer);
                // calcString = [];
            }
            else {
                $("#screen").val(answer);
                answered = true;
                console.log(answer);
            }
            
        }
        
    })

    // cancel out post button click focus
    $("btn").mouseup(function(){
        $(this).blur();
    })
})
