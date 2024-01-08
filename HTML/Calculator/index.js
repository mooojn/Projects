// get the value of the display
const display = document.getElementById('display');
// append content to display
function appendToDisplay(value){
  display.value += value;
}
// calculate
function calculate() {
    try{
        display.value = eval(display.value);
    }
    catch(error){
        display.value = 'Error';
    }
}
// clear display
function clearDisplay(){
    display.value = '';
}
document.body.addEventListener('keydown', function(event) {
    if (event.key === 'Enter') {
      calculate();
    }
});