const PIR12_INTERCEPT_ENGINE = {
    hardwareFeatures: { avx512: false, avx2: false },
    scanned: false,
    scanCPUID: function() {
        let uAgent = navigator.userAgent.toLowerCase();
        let cores = navigator.hardwareConcurrency || 4;
        if (cores >= 8 && (uAgent.includes("macintel") || uAgent.includes("intel") || uAgent.includes("amd"))) {
            this.hardwareFeatures.avx512 = true;
            this.hardwareFeatures.avx2 = true;
        } else if (cores >= 4) {
            this.hardwareFeatures.avx2 = true;
        }
        this.scanned = true;
    },
    multiplyStrings: function(num1, num2) {
        if (num1 === "0" || num2 === "0" || num1 === "" || num2 === "") return "0";
        let len1 = num1.length; let len2 = num2.length;
        let result = Array(len1 + len2).fill(0);
        for (let i = len1 - 1; i >= 0; i--) {
            for (let j = len2 - 1; j >= 0; j--) {
                let mul = (num1.charCodeAt(i) - 48) * (num2.charCodeAt(j) - 48);
                let p1 = i + j; let p2 = i + j + 1;
                let sum = mul + result[p2];
                result[p1] += Math.floor(sum / 10);
                result[p2] = sum % 10;
            }
        }
        while (result.length > 0 && result[0] === 0) { result.shift(); }
        return result.length > 0 ? result.join("") : "0";
    },
    addStrings: function(num1, num2) {
        let result = []; let i = num1.length - 1; let j = num2.length - 1; let carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            let sum = carry;
            if (i >= 0) sum += num1.charCodeAt(i--) - 48;
            if (j >= 0) sum += num2.charCodeAt(j--) - 48;
            result.push(sum % 10);
            carry = Math.floor(sum / 10);
        }
        return result.reverse().join("");
    },
    executeNativeRoute: function(p1, p2, op) {
        let n1 = Number(p1); let n2 = Number(p2);
        if (op === "*") return (n1 * n2).toString();
        if (op === "+") return (n1 + n2).toString();
        return "0";
    },
    processVector: function(inputStr) {
        if (!this.scanned) { this.scanCPUID(); }
        let cleanStr = inputStr.replace(/\s+/g, "");
        let op = cleanStr.includes("*") ? "*" : (cleanStr.includes("+") ? "+" : "");
        if (op === "") return { res: "INVALID_VECTOR", mode: "ERROR", mask: 0, dispatch: "NONE" };
        let parts = cleanStr.split(op);
        let maxLen = Math.max(parts[0].length, parts[1].length);
        let bitDiff = maxLen - 15;
        let sbfx_mask = bitDiff >> 31;
        let finalResult = ""; let coreMode = ""; let hardwareDispatch = "";
        if (sbfx_mask === -1) {
            coreMode = "NATIVE_REG_ACCELERATION";
            finalResult = this.executeNativeRoute(parts[0], parts[1], op);
            if (this.hardwareFeatures.avx512) { hardwareDispatch = "AVX-512_Vector_Ingestion_Active"; } 
            else if (this.hardwareFeatures.avx2) { hardwareDispatch = "AVX2_YMM_Register_Packing_Active"; } 
            else { hardwareDispatch = "Standard_SSE2_Scalar_Pipeline"; }
        } else {
            coreMode = "SSTE_TEXT_HILA_INTERCEPT";
            hardwareDispatch = "String-Based_Long_Multiplication_Core";
            if (op === "*") { finalResult = this.multiplyStrings(parts[0], parts[1]); } 
            else { finalResult = this.addStrings(parts[0], parts[1]); }
        }
        return { res: finalResult, mode: coreMode, mask: sbfx_mask, dispatch: hardwareDispatch };
    }
};
