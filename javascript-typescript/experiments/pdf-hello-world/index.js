const { jsPDF } = require("jspdf");

(async () => {
    const doc = new jsPDF();

    const centerX = doc.internal.pageSize.getWidth() / 2;

    doc.setFontSize(20);
    doc.setFont("helvetica", "bold");
    doc.text("Hello World", centerX, 10, {
        align: "center",
    });

    doc.setFontSize(12);
    doc.setFont("helvetica", "normal");
    doc.text("Some long paragraph", centerX, 20, { align: "center" });

    const res = await fetch("https://picsum.photos/200");
    const blob = await res.blob();
    const buffer = await blob.arrayBuffer();
    const data = new Uint8Array(buffer);

    const size = 100;

    doc.addImage(data, "JPEG", centerX - size / 2, 30, size, size);

    doc.text("The end", 10, size + 40);

    doc.save("test.pdf");
})();
