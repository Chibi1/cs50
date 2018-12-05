// console.log("Hello World");

var calcString = [""];
var answer = "0";
answered = true;
operating = false;
bracket = true;
powered = false;

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
                operating = false;
                bracket = false;
                calcString = [];
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            else {
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            
        }
        // operator "checks" for appending value to array
        if (["+", "-", "*", "/", "."].includes(value)) {
            if (operating == false) {
                answered = false;
                operating = true;
                bracket = false;
                calcString.push(value);
                $("#screen").val(calcString.join(""));
                // console.log(calcString[-1]);
            }
        }
        // implement parenthesis
        if (["(", ")"].includes(value) && (operating == true || bracket == true)) {
            operating = false;
            calcString.push(value);
            $("#screen").val(calcString.join(""));
        }
        // implement power
        if (value == "^" && operating == false) {
            bracket = true;
            powered = true;
            calcString.unshift("(");
            calcString.push(")^(");
            $("#screen").val(calcString.join(""));
            console.log(calcString);
        }
        // implement delete button
        if (value == "DEL") {
            answer = 0;
            answered = true;
            operating = false;
            bracket = true;
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
                operating = true;
                bracket = false;
                console.log(answer);
                // calcString = [];
            }
            else {
                $("#screen").val(answer);
                answered = true;
                operating = false;
                bracket = true;     
                console.log(answer);
            }
            
        }
        
    })

    // cancel out post button click focus
    $("btn").mouseup(function(){
        $(this).blur();
    })
})
