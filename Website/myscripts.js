var xValues = ["12:30","13:00","13:30","14:00","14:30"]
var barcolors = ["black","green","blue","orange","cyan"]
var yValues = [123,234,120,45,56]
var myChart = new Chart("myChart", {
  type: "bar",
  data: {
    labels: xValues,
    datasets: [{
      backgroundColor: barcolors,
      data: yValues
    }]
  },
  options: {}
});
