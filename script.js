let history = [""];
let current = 0;

function typeText() {
  const input = document.getElementById("inputText").value;
  if (input === "") return;
  const newText = history[current] + input;
  history = history.slice(0, current + 1);
  history.push(newText);
  current++;
  updateDisplay();
  document.getElementById("inputText").value = "";
}

function undo() {
  if (current > 0) {
    current--;
    updateDisplay();
  }
}

function redo() {
  if (current < history.length - 1) {
    current++;
    updateDisplay();
  }
}

function clearText() {
  history = [""];
  current = 0;
  updateDisplay();
}

function updateDisplay() {
  document.getElementById("displayText").innerText = history[current];
}
