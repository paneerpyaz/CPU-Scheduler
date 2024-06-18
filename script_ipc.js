const { ipcRenderer } = require('electron');

const runSchedulerBtn = document.getElementById('runSchedulerBtn');
const resultElement = document.getElementById('result');
const averageBox = document.getElementById('averageBox');
const averageTATElement = document.getElementById('averageTAT');
const averageWTElement = document.getElementById('averageWT');
const cpuOverheadElement = document.getElementById('cpuOverhead'); // Added for displaying CPU overhead

runSchedulerBtn.addEventListener('click', () => {
    const algorithm = document.getElementById('algorithmSelect').value;
    const input = document.getElementById('processInput').value;

    console.log('Sending runScheduler event with algorithm:', algorithm);
    console.log('Input:', input);

    ipcRenderer.send('runScheduler', { algorithm, input });
});

ipcRenderer.on('schedulerResult', (event, { error, result }) => {
    if (error) {
        console.log(`Scheduler error: ${error}`);
        resultElement.innerText = `Error: ${error}`;
        resultElement.classList.add('text-danger');
        resultElement.classList.remove('text-success');
    } else {
        console.log('Scheduler result:', result);
        const { processes, averageTAT, averageWT, schedulingOverhead } = result;
        resultElement.innerText = `Processes: ${JSON.stringify(processes, null, 2)}`;
        
        averageTATElement.innerText = `Average Turnaround Time: ${averageTAT}`;
        averageWTElement.innerText = `Average Waiting Time: ${averageWT}`;
        cpuOverheadElement.innerText = `Scheduling Overhead: ${schedulingOverhead.toFixed(12)} s`; // Updated to show float value with units

        averageBox.style.display = 'block';
        renderGanttChart(processes);
        resultElement.classList.add('text-success');
        resultElement.classList.remove('text-danger');
    }
});
function renderGanttChart(processes) {
    d3.select("#gantt-chart").select("svg").remove();

    const margin = { top: 20, right: 20, bottom: 30, left: 50 };
    const width = 960 - margin.left - margin.right;
    const height = 500 - margin.top - margin.bottom;

    const x = d3.scaleLinear().range([0, width]);
    const y = d3.scaleBand().range([height, 0]).padding(0.1);

    const svg = d3.select("#gantt-chart").append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    let ganttData = processes.map((process, index) => ({
        task: `Process ${process.id}`,
        startTime: process.arrivalTime,
        endTime: process.arrivalTime + process.burstTime
    }));
    const color = d3.scaleOrdinal(d3.schemeCategory10); 
    x.domain([0, d3.max(ganttData, d => d.endTime)]);
    y.domain(ganttData.map(d => d.task));
    svg.selectAll(".bar")
        .data(ganttData)
        .enter().append("rect")
        .attr("class", "bar")
        .attr("x", d => x(d.startTime))
        .attr("y", d => y(d.task))
        .attr("width", d => x(d.endTime) - x(d.startTime))
        .attr("height", y.bandwidth())
        .attr("fill", d => color(d.task));
    svg.append("g")
        .attr("class", "x axis")
        .attr("transform", "translate(0," + height + ")")
        .call(d3.axisBottom(x).ticks(10).tickFormat(d => `${d} ms`))
        .selectAll("text") 
        .style("fill", "black"); 
    svg.append("g")
        .attr("class", "y axis")
        .call(d3.axisLeft(y))
        .selectAll("text") 
        .style("fill", "black"); 
}
