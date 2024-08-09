const ws = new WebSocket("ws://localhost:7031/websocket");

ws.addEventListener("open", () => {
    console.log("We are connected!");
});

ws.addEventListener("message", e => {
    try {
        const altered = JSON.parse(e.data);
        console.log(altered);
        if(data["selected_table"] === table_options.value) {
            query_data();
        }
    } catch(e) {
        console.log(e);
    }
});

let default_selected = false

let table_options = document.getElementById("table_options")
class table_option {
    constructor(id, name, fields) {
        this.id = id
        this.fields = fields

        table_options.innerHTML += `<option value="${id}" ${!default_selected ? "selected" : ""}>${name}</option>`

        this.data_format = `<tr>`
        for (let field of fields) {
            this.data_format += `\n<th>${field}</th>`
        }
        this.data_format += "</tr>"

        if (!default_selected) this.set_table()
        default_selected = true
    }

    set_table() {
        document.getElementById("data").innerHTML = this.data_format
    }
}

let table_maps = {}
table_maps["remedio"] = new table_option("remedio", "Remédios", ["Nome", "Tarja"])
table_maps["receita"] = new table_option("receita", "Receitas", ["ID", "Medico", "Paciente", "Posto"])
table_maps["receitaremedio"] = new table_option("receitaremedio", "Receitas Remédios", ["Receita", "Remedio", "Prontidao"])
table_maps["usuario"] = new table_option("usuario", "Usuários", ["CPF", "Email", "Senha"])
table_maps["farmaceutico"] = new table_option("farmaceutico", "Farmacêuticos", ["Usuario", "Posto"])
table_maps["medico"] = new table_option("medico", "Médicos", ["Usuario", "Posto"])
table_maps["paciente"] = new table_option("paciente", "Pacientes", ["Usuario", "Convenio", "Posto"])
table_maps["regiao"] = new table_option("regiao", "Regiões", ["ID", "Nome"])
table_maps["tarja"] = new table_option("tarja", "Tarjas", ["Nome", "Retencao"])
table_maps["posto"] = new table_option("posto", "Postos", ["ID", "Nome", "Regiao"])
table_maps["estoqueregional"] = new table_option("estoqueregional", "Estoques Regionais", ["ID", "Regiao"])
table_maps["estoqueregionalremedio"] = new table_option("estoqueregionalremedio", "Estoque Regional Remédios", ["Estoque Regional", "Remedio", "Quantidade"])
table_maps["estoquelocal"] = new table_option("estoquelocal", "Estoques Locais", ["ID", "Regiao"])
table_maps["estoquelocalremedio"] = new table_option("estoquelocalremedio", "Estoque Local Remédios", ["Estoque Local", "Remedio", "Quantidade"])

function change_table() {
    table_maps[table_options.value].set_table()
}

async function query_data() {
    // Get the selected table id
    let selected_table = table_options.value;

    // Get the filter value
    let filter_value = document.getElementById("filters").value;

    // Construct the API endpoint with query parameters for local testing
    let api_url = `http://andromeda.lasdpc.icmc.usp.br:7031/${selected_table}/${encodeURIComponent(filter_value)}`;

    try {
        // Make a request to the server
        let response = await fetch(api_url);

        // Check if the response is okay
        if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`);
        }

        // Parse the response as JSON
        let data = await response.json();

        // Update the table with the fetched data
        update_table(data, selected_table);
    } catch (error) {
        console.error('Failed to fetch data:', error);
    }
}

// Function to update the table with fetched data
function update_table(data, selected_table) {
    // Clear the current table content
    let table = document.getElementById("data");
    table.innerHTML = "";

    // Get the header fields from the table_map
    let fields = table_maps[selected_table].fields;

    // Create the table header
    let header_row = "<tr>";
    fields.forEach(field => {
        header_row += `<th>${field}</th>`;
    });
    header_row += "</tr>";
    table.innerHTML += header_row;

    // Create the table rows from the fetched data
    data.forEach(row => {
        let row_html = "<tr>";
        fields.forEach(field => {
            // Convert field to lowercase to match JSON keys
            row_html += `<td>${row[field.toLowerCase()]}</td>`;
        });
        row_html += "</tr>";
        table.innerHTML += row_html;
    });
}