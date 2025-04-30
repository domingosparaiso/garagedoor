#pragma once

const char *testHtml = R"literal(
  <!DOCTYPE html>
  <body style='width:480px'>
    <h1>TESTES</h1>
    <hr>
    <input type=button value='ABRE' onclick='abre();'><br>
    <input type=button value='FECHA' onclick='fecha();'><br>
    <input type=button value='GARAGEM' onclick='garagem();'><br>
    <input type=button value='ACENDE' onclick='acende();'><br>
    <input type=button value='APAGA' onclick='apaga();'><br>
    <input type=button value='LUZ' onclick='luz();'><br>
    <input type=button value='STATUS' onclick='status();'><br>
    <hr>
    <div id='status'></div><hr>
    <div id='sensor'></div><hr>
  </body>
  <script>
    function abre() { fetch('/open'); }
    function fecha() { fetch('/close'); }
    function garagem() { fetch('/garage'); }
    function acende() { fetch('/on'); }
    function apaga() { fetch('/off'); }
    function luz() { fetch('/light'); }
    function status() {
        fetch('/status')
            .then(x => x.text())
            .then((out) => {
                document.getElementById('status').innerHTML = out;
        }
        fetch('/sensor')
            .then(x => x.text())
            .then((out) => {
                document.getElementById('sensor').innerHTML = out;
        }
    }
  </script>
</body>
</html>
)literal";
