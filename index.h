document
    .getElementById("overlay")
    .classList.remove("show");

};


/* AUTH */

window.openAuth = function() {

    document
    .getElementById("authModal")
    .classList.add("show");

};


window.closeAuth = function() {

    document
    .getElementById("authModal")
    .classList.remove("show");

};


function getCredentials() {

    return {

        email:
        document
        .getElementById("email")
        .value
        .trim(),

        password:
        document
        .getElementById("password")
        .value

    };

}


/* CREATE ACCOUNT */

window.signUp = async function() {

    const {
        email,
        password
    } = getCredentials();

    const message =
    document.getElementById("authMessage");


    if(!email || !password) {

        message.textContent =
        "Please enter your email and password.";

        return;
    }


    try {

        await
        createUserWithEmailAndPassword(
            auth,
            email,
            password
        );

        message.textContent =
        "Account created successfully ✦";

    }

    catch(error) {

        message.textContent =
        error.message;

    }

};


/* LOGIN */

window.login = async function() {

    const {
        email,
        password
    } = getCredentials();

    const message =
    document.getElementById("authMessage");


    try {

        await
        signInWithEmailAndPassword(
            auth,
            email,
            password
        );

        message.textContent =
        "Welcome back to Elora Nox ✦";

    }

    catch(error) {

        message.textContent =
        error.message;

    }

};


/* USER STATUS */

onAuthStateChanged(
    auth,
    user => {

        const button =
        document.querySelector(".user-btn");

        if(user) {

            button.textContent =
            "LOGOUT";

            button.onclick =
            async () => {

                await signOut(auth);

                button.textContent =
                "ACCOUNT";

                button.onclick =
                window.openAuth;

            };

        }

        else {

            button.textContent =
            "ACCOUNT";

            button.onclick =
            window.openAuth;

        }

    }
);


/* PLACE ORDER */

window.placeOrder =
async function() {

    const user =
    auth.currentUser;


    if(!user) {

        alert(
            "Please create an account or login before placing an order."
        );

        openAuth();

        return;

    }


    if(cart.length === 0) {

        alert(
            "Your bag is empty."
        );

        return;

    }


    const total =
    cart.reduce(
        (sum,item) =>
        sum + item.price,
        0
    );


    try {

        await addDoc(
            collection(db,"orders"),
            {

                userId:
                user.uid,

                customerEmail:
                user.email,

                products:
                cart.map(item => ({

                    name:
                    item.name,

                    price:
                    item.price

                })),

                total:
                total,

                status:
                "pending",

                createdAt:
                serverTimestamp()

            }
        );


        alert(
            "Your order has been received ✦"
        );


        cart = [];

        updateCart();

        closeCart();

    }

    catch(error) {

        console.error(error);

        alert(
            "There was a problem saving your order."
        );

    }

};

</script>

</body>
</html>
