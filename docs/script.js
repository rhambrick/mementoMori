const dobInput = document.getElementById('dob');
const saveDobBtn = document.getElementById('saveDob');
const countdownDiv = document.getElementById('countdown');
const secondsLeftDiv = document.getElementById('secondsLeft');
const dobInputDiv = document.getElementById('dob-input');
const resetBtn = document.getElementById('resetBtn');

// Set max date to today to prevent future DOB
dobInput.max = new Date().toISOString().split('T')[0];

function getSecondsLeft(dob) {
  const lifeSpanSeconds = 72 * 365.25 * 24 * 60 * 60;
  const deathDate = new Date(dob.getTime() + lifeSpanSeconds * 1000);
  const now = new Date();
  let diff = Math.floor((deathDate - now) / 1000);
  if (diff < 0) diff = 0;
  return diff;
}

function updateCountdown() {
  const dobStr = localStorage.getItem('dob');
  if (!dobStr) return;
  const dob = new Date(dobStr);
  const secondsLeft = getSecondsLeft(dob);
  secondsLeftDiv.textContent = secondsLeft.toLocaleString() + '';
}

function showCountdown() {
  dobInputDiv.style.display = 'none';
  countdownDiv.style.display = 'block';
  updateCountdown();
}

function showDobInput() {
  dobInputDiv.style.display = 'block';
  countdownDiv.style.display = 'none';
}

saveDobBtn.onclick = () => {
  const dobValue = dobInput.value;
  if (!dobValue) {
    alert('Please select your birthday');
    return;
  }
  localStorage.setItem('dob', dobValue);
  showCountdown();
  setInterval(updateCountdown, 1000);
}

resetBtn.onclick = () => {
  localStorage.removeItem('dob');
  showDobInput();
}

// On page load
window.onload = () => {
  const dobStr = localStorage.getItem('dob');
  if (dobStr) {
    showCountdown();
    setInterval(updateCountdown, 1000);
  } else {
    showDobInput();
  }
};
