
# sell() method code in application.py

        # # CODE TO KEEP CLEAN DATABASE (ONLY IF TRANSACTION HISTORY IS NOT REQUIRE)

        # # remember the stock and shares to sell for fast access
        # please_sell_stock = request.form.get("symbol")
        # please_sell_shares = request.form.get("shares")

        # try:
        #     # Of the stock the user requested, get the number of shares they have to sell
        #     shares_sellable = db.execute("SELECT id, shares FROM portfolio WHERE symbol = :symbol AND user_id = :user_id", user_id = session.get("user_id"), symbol = request.form.get("symbol") )

        # except RuntimeError:
        #     # If the database query failed, apologize to the user.
        #     return apology("Error: We'll fix this. Please try again shortly.")


        # # Track shares left to sell
        # shares_left_to_sell = int(please_sell_shares)

        # # track current row with a loop counter
        # ctr = 0

        # # loop through the rows where the users stock is stored
        # while shares_left_to_sell > 0:

        #     # if the row has fewer shares than the shares we need to sell
        #     # and if the row has positive number of shares
        #     # (i.e. not a row created from the sale of stock)
        #     if ( shares_sellable[ctr]["shares"] < shares_left_to_sell & shares_sellable[ctr]["shares"] > 0 ):

        #         # decrease the number of shares we still need to sell
        #         shares_left_to_sell = shares_left_to_sell - shares_sellable[ctr]["shares"]

        #         # identify the row to delete
        #         relevant_row = shares_sellable[ctr]["id"]

        #         try:
        #             # delete the row
        #             delete_row = db.execute("DELETE FROM portfolio WHERE id = :relevant_row", relevant_row = relevant_row)

        #         except RuntimeError:
        #             # If the database query failed, apologize to the user.
        #             return apology("Error: We'll fix this. Please try again shortly.")


        #     # otherwise if the row has the exact number of shares we need to sell
        #     elif ( shares_sellable[ctr]["shares"] == shares_left_to_sell):

        #         # identify the row to delete
        #         relevant_row = shares_sellable[ctr]["id"]

        #         try:
        #             # delete the row
        #             delete_row = db.execute("DELETE FROM portfolio WHERE id = :stock_id", stock_id = relevant_row)

        #         except RuntimeError:
        #             # If the database query failed, apologize to the user.
        #             return apology("Error: We'll fix this. Please try again shortly.")

        #         # reduce shares left to sell to zero
        #         shares_left_to_sell = 0

        #     # otherwise if there are more shares in this row than we need to sell
        #     # and we have not sold all the necessary shares
        #     elif ( shares_sellable[ctr]["shares"] > shares_left_to_sell):

        #         # figure out how many shares will be left in the row
        #         # after we remove the stocks we want to sell
        #         new_share_number = shares_sellable[ctr]["shares"] - shares_left_to_sell

        #         # identify the row to update
        #         relevant_row = shares_sellable[ctr]["id"]

        #         try:
        #             # update the row
        #             update_row = db.execute("UPDATE portfolio SET shares = :new_share_number WHERE id = :id", new_share_number = new_share_number, id = relevant_row)

        #         except RuntimeError:
        #             # If the database query failed, apologize to the user.
        #             return apology("Error: We'll fix this. Please try again shortly.")

        #         # reduce shares left to sell to zero
        #         shares_left_to_sell = 0

        #     # track current row with a loop counter
        #     ctr += 1
