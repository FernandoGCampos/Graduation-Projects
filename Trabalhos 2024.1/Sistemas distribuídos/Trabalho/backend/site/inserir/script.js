const ws = new WebSocket("ws://localhost:7031/websocket");

ws.addEventListener("open", () => {
    console.log("We are connected!");
});

// Event listener on message only at search page
// ws.addEventListener("message", e => {
//     try {
//         console.log(JSON.parse(e.data));
//     } catch(error) {
//         console.log(error);
//     }
// });

let default_selected = false;

let table_options = document.getElementById("table_options");
let form_container = document.getElementById("form_container");

class TableOption {
    constructor(id, name, fields) {
        this.id = id;
        this.fields = fields;
        table_options.innerHTML += `<option value="${id}" ${!default_selected ? "selected" : ""}>${name}</option>`;

        if (!default_selected) this.setTable();
        default_selected = true;
    }

    setTable() {
        this.generateFormFields();
    }

    generateFormFields() {
        form_container.innerHTML = ''; // Limpa os campos anteriores
        for (let field of this.fields) {
            let input_html = `<label for="${field}">${field}</label><input type="text" id="${field}" name="${field}"><br/>`;
            form_container.innerHTML += input_html;
        }
    }
}

let table_maps = {
    remedio: new TableOption("remedio", "Remédios", ["Nome", "Tarja"]),
    receita: new TableOption("receita", "Receitas", ["ID", "Médico", "Paciente", "Posto"]),
    receitaremedio: new TableOption("receitaremedio", "Receitas Remédios", ["Receita", "Remedio", "Prontidão"]),
    usuario: new TableOption("usuario", "Usuários", ["CPF", "Email", "Senha"]),
    farmaceutico: new TableOption("farmaceutico", "Farmacêuticos", ["Usuário", "Posto"]),
    medico: new TableOption("medico", "Médicos", ["Usuário", "Posto"]),
    paciente: new TableOption("paciente", "Pacientes", ["Usuário", "Convênio", "Posto"]),
    regiao: new TableOption("regiao", "Regiões", ["Nome"]),
    tarja: new TableOption("tarja", "Tarjas", ["Nome", "Retenção"]),
    posto: new TableOption("posto", "Postos", ["ID", "Nome", "Região"]),
    estoqueregional: new TableOption("estoqueregional", "Estoques Regionais", ["ID", "Região"]),
    estoqueregionalremedio: new TableOption("estoqueregionalremedio", "Estoque Regional Remédios", ["Estoque Regional", "Remédio", "Quantidade"]),
    estoquelocal: new TableOption("estoquelocal", "Estoques Locais", ["ID", "Região"]),
    estoquelocalremedio: new TableOption("estoquelocalremedio", "Estoque Local Remédios", ["Estoque Local", "Remédio", "Quantidade"])
};

function change_table() {
    table_maps[table_options.value].setTable();
}

window.onload = function() {
    change_table(); // Chama a função para configurar a tabela inicial ao carregar a página
};


async function submit_data() {
    let selected_table = table_options.value;
    let fields = table_maps[selected_table].fields;
    let data = {};

    fields.forEach(field => {
        data[field.toLowerCase()] = document.getElementById(field).value;
    });
    console.log(selected_table)

    let api_url = `http://andromeda.lasdpc.icmc.usp.br:7031/${selected_table}/`;

    console.log(JSON.stringify(data))

    try {
        let response = await fetch(api_url, {
            method: 'POST',
            body: JSON.stringify(data)
        });

        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        let result = await response.json();
        console.log('Server response:', result);
        alert('Dados enviados com sucesso!');
        data["selected_table"] = selected_table;
        send_ws(data);
    } catch (error) {
        console.error('Failed to send data:', error);
        alert('Erro ao enviar dados.');
    }
}

function send_ws(data) {
    ws.send(JSON.stringify(data));
}