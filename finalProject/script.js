// console.log("Hello World");

var calcString = [];
var power = []
var answer = "0";
answered = true;
operating = false;
inBracket = false;
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
                calcString = [];
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            else {
                operating = false;
                calcString.push(value);
                $("#screen").val(calcString.join(""));
            }
            
        }
        // operator "checks" for appending value to array
        if (["+", "-", "*", "/", "."].includes(value)) {
            if (operating == false) {
                answered = false;
                operating = true;
                calcString.push(value);
                $("#screen").val(calcString.join(""));
                // console.log(calcString[-1]);
            }
        }
        // implement parenthesis
        if (value == "(") {
            operating = true;
            inBracket = true;
            calcString.push(value);
            $("#screen").val(calcString.join(""));
        }
        else if (value == ")") {
            operating = false;
            inBracket = false;
            calcString.push(value);
            $("#screen").val(calcString.join(""));
        }
        // implement power
        if (value == "x^y" && operating == false) {
            answered = false;
            operating = true;
            inBracket = true;
            powered = true;
            calcString.unshift("(");
            calcString.push(")^(");
            var base = calcString.join("")
            $("#screen").val(base);
            console.log(base);            
        }
        if (value == ")" && powered == true && inBracket == false) {
            inBracket = false;
            powered = false;
            Math.pow()
        }
        // implement delete button
        if (value == "DEL") {
            answer = 0;
            answered = true;
            operating = false;
            inBracket = false;
            $("#screen").val(answer);
            console.log(answer);
            calcString = [];
        }
        
        // update calculator screen
        if (value != "=") {
            
            console.log(calcString.join(""));
        }
        else {
            if (calcString.length != 0) {
                answer = eval(calcString.join(""));
                $("#screen").val(answer);
                answered = true;
                operating = false;
                inBracket = false;
                console.log(answer);
                // calcString = [];
            }
            else {
                $("#screen").val(answer);
                answered = true;
                operating = false;
                inBracket = true;     
                console.log(answer);
            }
            
        }

        console.log("answered: " + answered);
        console.log("operating: " + operating);
        console.log("inBracket: " + inBracket);
        console.log("powered: " + powered);
        
    })
    

    // cancel out post button click focus
    $(".btn").mouseup(function(){
        $(this).blur();
    })
})
